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
const int N = 1000005;
const int C = 1000000;
const int K = 2005;
int n, m, k;
int mu[N], sm[N], pri[N / 9], cnt, s[K];
bool vis[N];
LL ans;
unordered_map <int, int> _mu, dp[K];
int gcd(int x, int y) {return !y ? x : gcd(y, x % y);}
void init() {
	mu[1] = 1;
	for (int i = 2; i <= C; ++ i) {
		if (!vis[i]) pri[++cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt && i * pri[j] <= C; ++ j) {
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
			mu[i * pri[j]] = - mu[i];
		}
	}
	for (int i = 1; i <= C; ++ i) sm[i] = mu[i] + sm[i - 1];
	for (int i = 1; i <= k; ++ i) s[i] = s[i - 1] + (gcd(i, k) == 1);
}
int smu(int x) {
	if (x <= C) return sm[x];
	if (_mu[x]) return _mu[x];
	int res = 1;
	for (int l = 2, r; l <= x; l = r + 1)
		r = x / (x / l), res -= (r - l + 1) * smu(x / l);
	return _mu[x]=res;
}
int h(int x) {return s[k] * (x / k) + s[x % k];}//for i 1 x :[gcd(i,k)=1]
int g(int n, int k) {
	if (!n) return 0;
	if (k == 1) return dp[k][n] = smu(n);
	if (dp[k][n]) return dp[k][n];
	int res = 0;
	for (int i = 1; i * i <= k; ++ i) {
		if (k % i == 0) {
			if (mu[i]) res += mu[i] * mu[i] * g(n / i, i);
			if (mu[k / i] && i * i != k) res += mu[k / i] * mu[k / i] * g(n / (k / i), k / i);
		}
	}
	return dp[k][n] = res;
}
signed main(){
	n = read(), m = read(), k = read(), init();
	for (int l = 1, r, mx = min(n, m); l <= mx; l = r + 1) {
		r = min(n / (n / l), m / (m / l));
		ans += 1ll * (n / l) * h(m / l) * (g(r, k) - g(l - 1, k));
	}
	printf("%lld\n", ans);
	return 0;
}
/*
1000000000 99999999 1926
30114906314949722

904 791040170 780
168263165839

*/