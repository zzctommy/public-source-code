#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define x first
#define y second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 1000005
int n, H, T, id[N << 1], valp[N];
LL val[N << 1], sum[N << 1], Mxd, Mxlen, ans;
LL f[N], g[N], fa[N], dfn[N], tmr, loop[N], cnt, len[N];
bool onlp[N];
struct edge{
	int nxt, to, val;
}e[N << 1];
int head[N], num_edge;
void addedge(int fr, int to, int val) {
	++ num_edge;
	e[num_edge].val = val;
	e[num_edge].to = to;
	e[num_edge].nxt = head[fr];
	head[fr] = num_edge;
}
void dfs(int u, int ft){
	dfn[u] = ++ tmr;
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to; if (v == ft) continue;
		if (dfn[v]) {
			if (dfn[v] < dfn[u]) continue;
			loop[++ cnt] = v, onlp[v] = 1, valp[cnt] = e[i].val;
			while (v != u) loop[++ cnt] = fa[v], onlp[fa[v]] = 1, valp[cnt] = len[v], v = fa[v];
		}
		else fa[v] = u, len[v] = e[i].val, dfs(v, u);
	}
}
void getd(int u, int ft) {
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to; if (v == ft || onlp[v]) continue;
		getd(v, u);
		if (f[v] + e[i].val > f[u]) g[u] = f[u], f[u] = f[v] + e[i].val;
		else if (f[v] + e[i].val > g[u]) g[u] = f[v] + e[i].val;
	}
	Mxd = max(Mxd, f[u] + g[u]);
}
void solve(int rt){
	Mxd = Mxlen = 0;
	cnt = 0, dfs(rt, 0);
	for (int i = 1; i <= cnt; ++ i) getd(loop[i], 0), loop[i + cnt] = loop[i], valp[i + cnt] = valp[i];
	for (int i = 1; i <= cnt << 1; ++ i) sum[i] = sum[i - 1] + valp[i];
	H = 1, T = 0;
	for (int i = 1; i <= cnt << 1; ++ i) {
		while (H <= T && id[H] <= i - cnt) ++ H;
		if (H <= T) Mxlen = max(Mxlen, val[H] + f[loop[i]] + sum[i]);
		LL w = f[loop[i]] - sum[i];
		while(H <= T && val[T] < w) -- T;
		++T, val[T] = w, id[T] = i;
	}
	ans += max(Mxlen, Mxd);
}
signed main() {
	n = read();
	for (int i = 1; i <= n; ++ i) {
		int x = i, y = read(), z = read();
		addedge(x, y, z), addedge(y, x, z);
	}
	for (int i = 1; i <= n; ++ i) if (!dfn[i]) solve(i);
	printf("%lld\n", ans);
	return 0;
}