#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int mod = 1e9 + 7;
int T, n, m;
const int N = 1e6 + 5;
int ivb[N], mu[N], fib[N], pri[N], cnt, f[N];
bool vis[N];
int qpow(int n, int k, int res = 1) {
	for(;k; k >>= 1, n = 1ll * n * n % mod)
		if (k & 1)res = 1ll * res * n % mod;
	return res;
}
int power(int n, int k){
	if (k == -1) return ivb[n];
	if (k == 0) return 1;
	if (k == 1) return fib[n];
}
void init(const int&N) {
	fib[1] = 1, mu[1] = 1, ivb[1] = 1;
	for (int i = 2; i <= N; ++ i) fib[i] = (fib[i - 1] + fib[i - 2]) % mod, ivb[i] = qpow(fib[i], mod - 2);
	for (int i = 2; i <= N; ++ i) {
		if(!vis[i]) pri[++ cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt && i * pri[j] <= N; ++ j) {
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
			mu[i * pri[j]] = - mu[i];
		}
	}
	for (int i = 0; i <= N; ++ i) f[i] = 1;
	for (int i = 1; i <= N; ++ i)
		for (int j = 1; i * j <= N; ++ j)
			f[i * j] = 1ll * f[i * j] * power(i, mu[j]) % mod;
//	for(int i=1;i<=10;++i)cout<<fib[i]<<' ';cout<<'\n';
//	for(int i=1;i<=10;++i)cout<<ivb[i]<<' ';cout<<'\n';
//	for(int i=1;i<=10;++i)cout<<mu[i]<<' ';cout<<'\n';
//	for(int i=1;i<=10;++i)cout<<f[i]<<' ';cout<<'\n';
	for (int i = 1; i <= N; ++ i) f[i] = 1ll * f[i] * f[i - 1] % mod;
}
int query(int n, int m){
	if(n > m) n ^= m ^= n ^= m;
	int res = 1;
	for(int l = 1, r;l <= n; l = r + 1) {
		r = min(n / (n / l), m / (m / l));
		res = 1ll * res * qpow(1ll * f[r] * qpow(f[l - 1], mod - 2) % mod, 1ll * (n / l) * (m / l) % (mod - 1)) % mod;
	}
	return res;
}
signed main() {
	init(N - 5);
	T = read();
	while(T --) {
		n = read(), m = read();
		printf("%d\n",query(n,m));
	}
}