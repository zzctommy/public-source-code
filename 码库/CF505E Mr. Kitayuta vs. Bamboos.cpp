#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define int long long
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}

const int N = 100005;
int n, m, k, p, h[N], a[N], v[N];

bool check(int md) {
	priority_queue <pair<int, int> > pq;
	for (int i = 1; i <= n; ++i)
		if (md - m * a[i] < h[i])
			v[i] = md, pq.push(mkp(-(md / a[i]), i));
	for (int i = 1; i <= m; ++i) {
		if (pq.empty()) break;
		for (int j = 1; j <= k; ++j) {
			if (pq.empty()) break;
			pair <int, int> now = pq.top();
			pq.pop();
			int id = now.se;
			if (v[id] - i * a[id] < 0) return 0;
			v[id] += p;
			if (v[id] - m * a[id] < h[id])
				pq.push(mkp(-(v[id] / a[id]), id));
		}
	}
	return pq.empty();
}

signed main() {
	n = read(), m = read(), k = read(), p = read();
	for (int i = 1; i <= n; ++i) h[i] = read(), a[i] = read();
	int l = 0, r = 1e15, res = 114514114514114514;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) res = mid, r = mid - 1;
		else l = mid + 1;
	}
	cout << res << '\n';
}