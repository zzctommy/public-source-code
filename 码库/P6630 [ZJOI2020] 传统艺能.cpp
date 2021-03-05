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
#define mod 998244353
inline int add(int x, int y) {return (x += y) >= mod ? x - mod : x;}
inline int sub(int x, int y) {return (x += mod - y) >= mod ? x - mod : x;}
inline int mul(int x, int y) {return 1ll * x * y % mod;}
inline int qpow(int n, int k) {
	int res = 1;
	for(; k; k >>= 1, n = 1ll * n * n % mod)
		if(k & 1) res = 1ll * n * res % mod;
	return res;
}
const int N = 400005;
int n, k, pw[N], ans, iv, s[N];
int L[N], R[N], fa[N], tot;
struct Matrix {
	int a[3][3];
	Matrix() { memset(a, 0, sizeof(a)); }
	inline void e(){ rep(i, 0, 2) rep(j, 0, 2) a[i][j]= i == j ; }
	inline int* operator [] (const int&k) { return a[k]; }
	inline Matrix operator * (const Matrix&t) const {
		Matrix res;
		rep(i, 0, 2) rep(j, 0, 2) rep(k, 0, 2) res.a[i][j] = add(res.a[i][j], mul(a[i][k], t.a[k][j]));
		return res;
	}
	inline Matrix operator ^ (int k) const {
		Matrix res, t=*this; res.e();
		for(; k; k >>= 1, t = t * t)
			if(k & 1) res = res * t;
		return res;
	}
};
int calc(int p) {
	int p1, p2, p3, p4, p5;
	if(p == 1) {
		p1 = sub(1, iv), p2 = iv;
		p3 = p4 = p5 = 0;
	} else {
		p1 = mul(sub(s[n], add(s[L[p] - 1], add(s[n - R[p]], mul(L[p], n - R[p] + 1)))), iv);
		p2 = mul(sub(mul(L[p], n - R[p] + 1), mul(L[fa[p]], n - R[fa[p]] + 1)), iv);
		p3 = mul(add(sub(s[L[p] - 1], s[L[fa[p]] - 1]), sub(s[n - R[p]], s[n - R[fa[p]]])), iv);
		p4 = mul(mul(L[fa[p]], n - R[fa[p]] + 1), iv);
		p5 = mul(add(s[L[fa[p]] - 1], s[n - R[fa[p]]]), iv);
	}
	assert(add(p1, add(p2, add(p3, add(p4, p5)))) == 1);
	Matrix A, B;
	A[0][0] = 0, A[0][1] = 1, A[0][2] = 1;
	B[0][0] = add(p4, p5);
	B[1][0] = sub(0, p3), B[1][1] = add(p3, p5);
	B[2][0] = add(p2, p3), B[2][1] = p1, B[2][2] = 1;
	A = A * (B ^ k);
	return A[0][0];
}
void dfs(int p) {
	ans = add(ans, calc(p));
	if(L[p] == R[p]) return;
	int mid = read();
	++tot, fa[tot] = p, L[tot] = L[p], R[tot] = mid, dfs(tot);
	++tot, fa[tot] = p, L[tot] = mid + 1, R[tot] = R[p], dfs(tot);
}
signed main(){
	n = read(), k = read(), iv = qpow(1ll * n * (n + 1) / 2 % mod, mod - 2);
	for(int i = 1; i <= n; ++i) s[i] = 1ll * i * (i + 1) / 2 % mod;
	++tot, fa[tot] = 0, L[tot] = 1, R[tot] = n, dfs(1);
	cout << ans << '\n';
	return 0;
}