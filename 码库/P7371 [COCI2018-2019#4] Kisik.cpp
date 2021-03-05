#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}

const int N = 1000006;
int n, k;
LL ans = 1e18, now;
pair<int, int> p[N];
multiset <int, greater<int> > s;
signed main(){
	n = read(), k = read();
	rep(i, 1, n) p[i].se = read(), p[i].fi = read();
	sort(p + 1, p + n + 1);
	rep(i, 1, n) {
		if(sz(s) < k) s.insert(p[i].se), now += p[i].se;
		else {
			int tmp = *s.begin();
			if(tmp > p[i].se) {
				now -= tmp - p[i].se;
				s.erase(s.begin()), s.insert(p[i].se);
			}
		}
		if(sz(s) == k) ckmin(ans, now * p[i].fi);
	}
	cout << ans << '\n';
}