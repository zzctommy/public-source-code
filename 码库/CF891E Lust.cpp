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

#define mod 1000000007
inline int qpow(int n, int k) {
	int res = 1;
	for(; k; k >>= 1, n = 1ll * n * n % mod)
		if(k & 1) res = 1ll * n * res % mod;
	return res;
}
const int N = 5005;
int n, k, a[N], f[N], ans;
typedef vector <int> poly;
poly A;
poly operator * (const poly&a,const poly&b) {
	poly res;
	int n = sz(a), m = sz(b);
	res.resize(n + m - 1);
	for(int i = 0; i < n + m - 2; ++i) res[i] = 0;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			res[i + j] = (res[i + j] + 1ll * a[i] * b[j] % mod) % mod;
	return res;
}

signed main() {
	n = read(), k = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	A.resize(2), A[0] = a[1], A[1] = mod - 1;
	for(int i = 2; i <= n; ++i) {
		static poly B;
		B.resize(2), B[0] = a[i], B[1] = mod - 1;
		A = A * B;
	}
 	f[0] = qpow(n, k);
	static const int ivn = qpow(n, mod - 2);
	for(int i = 1; i <= n; ++i)
		f[i] = 1ll * f[i - 1] * (k - i + 1) % mod * ivn % mod;
	for(int i = 0; i <= n; ++i)
		ans = (ans + 1ll * f[i] * A[i] % mod + mod) % mod;
	ans = 1ll * ans * qpow(qpow(n, k), mod - 2) % mod;
	int tmp = 1;
	for(int i = 1; i <= n; ++i) tmp = 1ll * tmp * a[i] % mod;
	ans = (tmp - ans + mod) % mod;
	cout << ans << '\n';	
	return 0;
}