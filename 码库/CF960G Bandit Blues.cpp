// Problem: G. Bandit Blues
// Contest: Codeforces - Divide by Zero 2018 and Codeforces Round #474 (Div. 1 + Div. 2, combined)
// URL: https://codeforces.com/problemset/problem/960/G
// Memory Limit: 256 MB
// Time Limit: 3500 ms

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

const int N = 200005;
const int M = N << 2;
#define mod 998244353

namespace math{
inline int qpow(int n, int k) { 
	int res = 1; 
	for (; k; k >>= 1, n = 1ll * n * n % mod) 
		if (k & 1) res = 1ll * n * res % mod; 
	return res;
}
int inv[N], fac[N], ifc[N];
void initmath(const int &n = N-1) {
	inv[1] = 1; for (int i = 2 ;i <= n; ++i) inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
	fac[0] = 1; for (int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	ifc[n] = qpow(fac[n], mod - 2); for(int i = n - 1; i >= 0; --i) ifc[i] =1ll * (i + 1) * ifc[i + 1] % mod;
}
}
using namespace math;

namespace poly{
	
int rev[M], lg, lim;
void init_poly(const int &n) {
	for (lg = 0, lim = 1; lim < n; ++lg, lim <<= 1);
	for (int i = 0; i < lim; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
}
void NTT(int *a, int op) {
	for (int i = 0; i < lim; ++i)
		if (i > rev[i]) swap(a[i], a[rev[i]]);
	const int g = op ? 3 : inv[3];
	for (int i = 1; i < lim; i <<= 1) {
		const int wn = qpow(g, (mod - 1) / (i << 1));
		for (int j = 0; j < lim; j += i << 1) {
			int w0 = 1;
			for (int k = 0; k < i; ++k, w0 = 1ll * w0 * wn % mod) {
				const int X = a[j + k], Y = 1ll * w0 * a[i + j + k] % mod;
				a[j + k] = (X + Y) % mod, a[i + j + k] = (X - Y + mod) % mod;
			} 
		}
	}
	if (op) return; const int ilim = qpow(lim, mod - 2);
	for (int i = 0; i < lim; ++i) a[i] = 1ll * ilim * a[i] % mod;
}
#define clr(a, n) memset(a, 0, sizeof(int) * (n))
#define cpy(a, b, n) memcpy(a, b, sizeof(int) * (n))
void poly_mul(int *f, int *g, int *ans, int n, int m) {
	static int A[M], B[M]; init_poly(n + m);
	cpy(A, f, n), clr(A + n, lim - n), NTT(A, 1);
	cpy(B, g, m), clr(B + m, lim - m), NTT(B, 1);
	for (int i = 0; i < lim; ++i) ans[i] = 1ll * A[i] * B[i] % mod;
	NTT(ans, 0);
}
void poly_shift(int *g, int*f, int n, int c) {
	static int A[M], B[M];
	for (int i = 0; i < n; ++i) A[i] = 1ll * f[i] * fac[i] % mod;
	for (int i = 0, j = 1; i < n; ++i, j = 1ll * j * c % mod) B[i] = 1ll * j * ifc[i] % mod;
	reverse(B, B + n), poly_mul(A, B, A, n, n);
	for (int i = 0; i < n; ++i) g[i] = 1ll * ifc[i] * A[i + n - 1] % mod;
}
void up_pow(int *g, int n) {
	static int A[M];
	if (n == 1) return g[0] = 0, g[1] = 1, void();
	if (n & 1) {
		up_pow(g, n - 1);
		for (int i = n; i > 0; --i) g[i] = (g[i - 1] + 1ll * g[i] * (n - 1) % mod) % mod;
	} else {
		up_pow(g, n / 2);
		poly_shift(A, g, n / 2 + 1, n / 2);
		poly_mul(g, A, g, n / 2 + 1, n / 2 + 1);
	}
}
void stirling1_row(int *g, int n) {	up_pow(g, n); }
	
}

int n, A, B, ans, sti[M];

signed main() {
	initmath();
	n = read(), A = read(), B = read();
	if (!A || !B || A + B - 2 > n - 1) return puts("0"), 0;
	if (n == 1) return puts("1"), 0;
	ans = 1ll * fac[A + B - 2] * ifc[A - 1] % mod * ifc[B - 1] % mod;
	poly::stirling1_row(sti, n - 1);
	ans = 1ll * ans * sti[A + B - 2] % mod;
	printf("%d\n", ans);
	return 0;
}