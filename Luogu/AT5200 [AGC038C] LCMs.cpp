#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N = 1000005;
const int M = N - 5;
const int mod = 998244353;
const int iv2 = (mod + 1) >> 1;
int n, c[N], mu[N], pri[N/9], cnt, f[N], ans, g[N], a[N];
bool vis[N];
void Sieve(const int&N) {
	mu[1] = 1;
	for (int i = 2; i <= N; ++ i) {
		if(!vis[i])pri[++cnt]=i,mu[i]=-1;
		for (int j = 1; i * pri[j] <= N; ++ j) {
			vis[i * pri[j]] = 1;
			if (i % pri[j]) mu[i * pri[j]] = - mu[i];
			else break;
		}
	}
	for (int i = 1; i <= N; ++ i)
		for (int j = 1; i * j <= N; ++ j)
		f[i * j] = (f[i * j] +1ll * mu[i] * i % mod) % mod;
	for (int i = 1; i <= N; ++ i)
		for (int j = 1; i * j <= N; ++ j)
			g[i] = (g[i] + 1ll * j * c[i * j]) % mod;
	for (int i = 1; i <= N; ++ i)
		ans = (ans + 1ll * i * f[i] % mod * g[i] % mod * g[i] % mod) % mod;
}
signed main() {
	n = read();
	for (int i = 1; i <= n; ++ i) ++c[a[i] = read()];
	Sieve(M);
	for(int i = 1; i <= n; ++ i) ans = (ans - a[i]) % mod;
	ans = 1ll * ans * iv2 % mod;
	printf("%d\n", (ans + mod) % mod);
	return 0;
}