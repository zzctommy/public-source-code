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
const int N = 500005;
int phi[N], pct, pri[N];
bool vis[N];
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
}
inline int gcd(int a, int b) {
	while(b) { int t = a % b; a = b, b = t; }
	return a;
}
signed main() {
	init();
	for(int T = read(); T; --T) {
		int a = read(), b = read(), g = gcd(a, b), t = (a + b) / g, ans = 0;
		for(int i = 1, x; i * i <= t; ++i) {
			if(t % i) continue;
			x = i, ans = (ans + 1ll * phi[t / x] * qpow(2, 1ll * g * x % (mod - 1)) % mod) % mod;
			if(i * i != t) x = t / i, ans = (ans + 1ll * phi[t / x] * qpow(2, 1ll * g * x % (mod - 1)) % mod) % mod;
		}
		ans = (qpow(2, a + b) - 1ll * ans * qpow(t, mod - 2) % mod + mod) % mod;
		printf("%d\n", ans);
	}
}