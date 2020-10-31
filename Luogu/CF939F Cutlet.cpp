#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define fi first
#define se second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 100005
#define K 105
#define inf 0x3f3f3f3f
int n, k, dp[2][N << 1], L[K], R[K];
int q[N << 1], H, T;
signed main() {
	n = read(), k = read();
	for (int i = 1; i <= k; ++ i) L[i] = read(), R[i] = read();
	dp[0][0] = 0;
	for (int i = 1; i <= n << 1; ++ i) dp[0][i] = inf;
	for (int i = 1, u = 1; i <= k; ++ i, u ^= 1) {
		for (int j = 0; j <= n; ++ j) dp[u][j] = dp[u ^ 1][j];
		H = 1, T = 0;
		for (int j = 0; j <= n; ++ j) {
			while (H <= T && dp[u ^ 1][j] <= dp[u ^ 1][q[T]]) -- T;
			q[++ T] = j;
			while (H <= T && q[H] < j - (R[i] - L[i])) ++ H;
			dp[u][j] = min(dp[u][j], dp[u ^ 1][q[H]] + 2);
		}
		H = 1, T = 0;
		for (int j = R[i]; j >= 0; -- j) {
			while (H <= T && dp[u ^ 1][R[i] - j] <= dp[u ^ 1][q[T]]) -- T;
			q[++ T] = R[i] - j;
			while (H <= T && q[H] < L[i] - j) ++ H;
			dp[u][j] = min(dp[u][j], dp[u ^ 1][q[H]] + 1);
		}
	}
	if (dp[k & 1][n] == inf) puts("Hungry");
	else printf("Full\n%d\n",dp[k & 1][n]);
	return 0;
}