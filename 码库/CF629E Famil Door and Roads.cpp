#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define mkp(x,y) make_pair(x,y)
#define fi first
#define se second
#define pb(x) push_back(x)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
#define N 100005
int n, m, dis[N];
LL f[N], g[N], s[N];
int head[N], num_edge;
struct edge{int nxt, to; } e[N << 1];
void addedge(int fr, int to) {
	++num_edge;
	e[num_edge].nxt = head[fr];
	e[num_edge].to = to;
	head[fr] = num_edge;
}
namespace Tree {

int siz[N], top[N], fa[N], son[N], dep[N];
void dfs1(int u, int ft) {
	siz[u] = 1;
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to; if (v == ft) continue;
		fa[v] = u, dep[v] = dep[u] + 1, dfs1(v, u), siz[u] += siz[v];
		if (siz[v] > siz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int tp) {
	top[u] = tp;
	if (son[u]) dfs2(son[u], tp);
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to; if (v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
}
int LCA(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) x ^= y ^= x ^= y;
		x = fa[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}
int jump(int x, int anc) {
	int res = 0;
	while (top[x] != top[anc]) res = top[x], x = fa[top[x]];
	return x == anc? res : son[anc];
}
void init(){dfs1(1, 0), dfs2(1, 1); }
}
using Tree::siz;
void dfs1(int u, int ft) {
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to; if (v == ft) continue;
		dis[v] = dis[u] + 1, dfs1(v, u), f[u] += f[v] + siz[v];
	}
}
void dfs2(int u, int ft) {
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to; if (v == ft) continue;
		s[v] = s[u] + (n - siz[v]) - siz[v], g[v] = s[v] - f[v], dfs2(v, u);
	}
}
signed main() {
	n = read(), m = read();
	for (int i = 1; i < n; ++ i) {
		int x = read(), y = read();
		addedge(x, y), addedge(y, x);
	}
	Tree::init(), dfs1(1, 0), s[1] = f[1], dfs2(1, 0);
	while (m --) {
		int x = read(), y = read(), lca = Tree::LCA(x, y);
		if (Tree::dep[x] > Tree::dep[y]) x ^= y ^= x ^= y;
		if (x == lca) {
			int t = Tree::jump(y, x);
			printf ("%.9lf\n", 1. * (f[y] * (n - siz[t]) + g[t] * siz[y])/ (1. * siz[y] * (n - siz[t]))+ 1. + dis[y] - dis[t]);
		}
		else printf ("%.9lf\n", 1. * (f[x] * siz[y] + f[y] * siz[x]) / (1. * siz[x] * siz[y])+ 1. + dis[x] + dis[y] - dis[lca] * 2);
	}
	return 0;
}