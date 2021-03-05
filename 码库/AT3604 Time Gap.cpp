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

const int N = 55;
int n, a[N], ans, c[N], b[N], d[N], tot;
vector <int> v1, v2;
int calc(int msk) {
	v2 = v1;
	for(int i = 0; i < tot; ++i)
		if(msk >> i & 1) v2.pb(24 - d[i]);
		else v2.pb(d[i]);
	sort(v2.begin(), v2.end());
	int res = 25;
	for(int i = 0; i < sz(v2) - 1; ++i) ckmin(res, v2[i + 1] - v2[i]);
	return res;
}
signed main() {
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read(), ++c[a[i]];
	for(int i = 0; i <= 12; ++i) {
		if(c[i] >= 3) return puts("0"), 0;
		else if(c[i] == 2) v1.pb(i), v1.pb(24 - i);
		else if(c[i] == 1) d[tot++] = i;
	}
	v1.pb(0), v1.pb(24);
	for(int msk = 0; msk < 1 << tot; ++msk)
		ckmax(ans, calc(msk));
	cout << ans << '\n';
	return 0;
}