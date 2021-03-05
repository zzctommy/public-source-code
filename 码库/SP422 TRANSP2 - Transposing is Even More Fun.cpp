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

#define mod 1000003
inline int qpow(int n, int k) {
	int res = 1;
	for(; k; k >>= 1, n = 1ll * n * n % mod)
		if(k & 1) res = 1ll * n * res % mod;
	return res;
}
const int N = 1000005;
int phi[N], pct, pri[N], pw2[N], inv[N];
bool vis[N];
int pool[N * 20], *mem = pool, *d[N], cnt[N];
void init() {
	phi[1] = 1;
	for(int i = 2; i < N; ++i) {
		if(!vis[i]) pri[++pct] = i, phi[i] = i - 1;
		for(int j = 1; j <= pct && i * pri[j] < N; ++j) {
			vis[i * pri[j]] = 1;
			if(i % pri[j] == 0) {
				phi[i * pri[j]] = phi[i] * pri[j];
				break;
			} else phi[i * pri[j]] = phi[i] * phi[pri[j]];
		}
	}
	for(int i = 1; i < N; ++i)
		for(int j = 1; i * j < N; ++j)
			++cnt[i * j];
	for(int i = 1; i < N; ++i) d[i] = mem, mem += cnt[i], cnt[i] = 0;
	for(int i = 1; i < N; ++i)
		for(int j = 1; i * j < N; ++j)
			d[i * j][cnt[i * j]++] = i;
	pw2[0] = 1;
	for(int i = 1; i < N; ++i) pw2[i] = (pw2[i - 1] << 1) % mod;
	inv[1] = 1;
	for(int i = 2; i < N; ++i) inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
}
inline int gcd(int a, int b) {
	while(b) { int t = a % b; a = b, b = t; }
	return a;
}
signed main() {
//	freopen("dt.in", "r", stdin);
//	freopen("1.out", "w", stdout);
	init();
	for(int T = read(); T; --T) {
		int a = read(), b = read();
		if(!a || !b) { puts("0"); continue; }
		int g = gcd(a, b), t = (a + b) / g, ans = 0;
		for(int i = 0; i < cnt[t]; ++i) {
			int x = d[t][i];
			ans = (ans + 1ll * phi[t / x] * pw2[g * x] % mod) % mod;
		}
		ans = (pw2[a + b] - 1ll * ans * inv[t] % mod + mod) % mod;
		printf("%d\n", ans);
	}
}