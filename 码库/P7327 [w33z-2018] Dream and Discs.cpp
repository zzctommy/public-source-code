//感谢ZAKY指导,验题变成补题可海星,验不动/kk
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
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N = 500005;
#define mod 1000000007
inline int qpow(int n, int k) {
	int res = 1; 
	for (; k; k >>= 1, n = 1ll * n * n % mod) 
		if (k & 1) res = 1ll * n * res % mod;
	return res;
}
const int iv6 = qpow(6, mod - 2);
int n, a[N], ALL, ans, pre[N], vis[N];

int f(int n){ return 1ll * iv6 * n % mod * (n + 1) % mod * (n + 2) % mod; }
int calc1(int x, int y) {
	// int res = 0;
	// rep(l, 1 + x, y) rep(r, y, n) {
	// 	rep(i, l, y - 1) rep(j, i, y - 1) ++res;
	// 	rep(i, y + 1, r) rep(j, i, r) ++res;
	// }
	// return res;
	return (1ll * (n - y + 1) * f(y - x - 1) % mod + 1ll * (y - x) * f(n - y) % mod) % mod;
}
int calc2(int x, int y) {
	// int res = 0;
	// rep(l, 1 + x, y) rep(r, y, n) rep(i, l, y) rep(j, y, r) ++res;
	// return res;
	return 1ll * (1ll * (y - x) * (y - x + 1) / 2 % mod) * (1ll * (n - y + 1) * (n - y + 2) / 2 % mod) % mod;
}
int calc3(int x, int y) {
	// int res = 0;
	// rep(l, 1, x) rep(r, y, n) rep(i, x + 1, y) rep(j, y, r) ++res;
	// return res;
	return 1ll * x * (y - x) % mod * (1ll * (n - y + 1) * (n - y + 2) / 2 % mod) % mod;
}

signed main() {
	n = read();
	for (int i = 1; i <= n; ++i) a[i] =read();
	for (int i = 1; i <= n; ++i) pre[i] = vis[a[i]], vis[a[i]] = i;
	for (int i = 1; i <= n; ++i) ALL = (ALL + 1ll * (n - i + 1) * i * (i + 1) / 2 % mod) % mod;
	for (int i = 1; i <= n; ++i) {
		int A1 = calc1(pre[i], i), A2 = calc1(0, a[i]);//第一次包含,第二次不包含.
		int B1 = calc2(pre[i], i), B2 = calc2(0, a[i]);//第一次包含,第二次也包含.
		int C = calc3(pre[i], i);//两次都包含i,第二次不包含pre[i].
		ans = (ans + 1ll * A1 * B2 % mod) % mod;
		ans = (ans + 1ll * A2 * B1 % mod) % mod;
		ans = (ans + 1ll * A1 * A2 % mod) % mod;
		ans = (ans - 1ll * C * B2 % mod + mod) % mod;
	}
	ans = 1ll * ans * qpow(1ll * ALL * ALL % mod, mod - 2) % mod;
	cout << ans << '\n';
}