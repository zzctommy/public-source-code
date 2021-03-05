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
#define int long long
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N = 100005;
int n, a[N], b[N], ans1 = 2e9, cnt[N], ans2;
set <int> s, s2;
inline bool cmp(const int &x, const int &y) {
	return a[x] < a[y];
}
signed main() {
	n = read();
	rep(i, 1, n) a[i] = read(), b[i] = i;
	sort(b + 1, b + n + 1, cmp);
	cnt[n] = 1;
	s.insert(0), s.insert(n + 1), s2.insert(n);
	per(i, n, 1) {
		if(sz(s2) == 1){
			int t = i / *s2.begin();
			if(ckmax(ans2, t) || ans2 == t)
				ckmin(ans1, a[b[i]] + 1);
		}
		int x = b[i];
		auto it = s.upper_bound(x);
		int suf = *it, pre = *(--it);
		if(!--cnt[suf - pre - 1]) s2.erase(suf - pre - 1);
		s.insert(x);
		if(x - 1 > pre) {
			if(!cnt[x - pre - 1]++) s2.insert(x - pre - 1);
		}
		if(x + 1 < suf) {
			if(!cnt[suf - x - 1]++) s2.insert(suf - x - 1);
		}
	}
	cout << ans1 << '\n';
}