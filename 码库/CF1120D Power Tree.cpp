//Orz cyn2006
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
int n, w[N], deg[N], num[N];
vector <int> ans;
LL dp[N][2], sum[N], g[N];
int hed[N], et;
bool lef[N], can[N][2];
struct edge { int nx, to; }e[N << 1];
void adde(int u, int v) { e[++ et].nx = hed[u], e[et].to = v, hed[u] = et; }
void dfs(int u, int ft) {
	if (deg[u] == 1 && u != 1) {
		dp[u][0] = w[u], dp[u][1] = 0, lef[u] = 1;
		return;
	}
	LL mx = 0;
	for (int i = hed[u]; i; i = e[i].nx) {
		int v = e[i].to; if (v == ft) continue;
		dfs(v, u);
		sum[u] += dp[v][0];
		if(mx < dp[v][0] - dp[v][1]) mx = dp[v][0] - dp[v][1], g[u] = mx, num[u] = 1;
		else if (mx == dp[v][0] - dp[v][1]) ++ num[u];
	}
	dp[u][1] = sum[u] - mx;
	dp[u][0] = min(dp[u][1] + w[u], sum[u]);
}
void calc(int u, int ft) {
	if (can[u][0] && dp[u][0] == dp[u][1] + w[u]) ans.pb(u);
	for (int i = hed[u]; i; i = e[i].nx) {
		int v = e[i].to; if (v == ft) continue;
		if (can[u][0]) {
			if (sum[u] - dp[v][0] + dp[v][1] + w[u] == dp[u][0]) can[v][1] = 1;
			if (sum[u] == dp[u][0] || g[u] != dp[v][0] - dp[v][1] || num[u] > 1) can[v][0] = 1;
		}
		if (can[u][1]) {
			if (g[u] == dp[v][0] - dp[v][1]) can[v][1] = 1;
			if (g[u] != dp[v][0] - dp[v][1] || num[u] > 1) can[v][0] = 1;
		}
		calc(v, u);
	}
}
signed main() {
	n=read();
	rep (i, 1, n) w[i] = read();
	rep (i, 2, n) {
		int x = read(), y = read();
		adde(x, y), adde(y, x), ++ deg[x], ++ deg[y];
	}
	dfs(1, 0), can[1][0] = 1, can[1][1] = dp[1][0] == dp[1][1] + w[1], calc(1, 0);
	// rep(i, 1, n) cerr << sum[i] << ' '; cerr << '\n';
	// rep(i, 1, n) cerr << g[i] << ' '; cerr << '\n';
	// rep(i, 1, n) cerr << dp[i][0] << ' ' << dp[i][1] << '\n';
	printf("%lld %d\n",dp[1][0], sz(ans));
	sort(ans.begin(), ans.end());
	rep(i, 0, sz(ans) - 1) printf("%d ", ans[i]);
	puts("");
	return 0;
}