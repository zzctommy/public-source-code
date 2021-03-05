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
const int N = 100005;
const int M = 200005;
int n, m, nu, nq, ans[M], tr[N], id[M];
int st[N], ed[N], tmr, top[N], fa[N], dep[N], son[N], siz[N];
struct edge{ int nx, to; } e[N << 1];
int hed[N], et;
inline void adde(int u, int v) {
	e[++et].nx = hed[u], e[et].to = v, hed[u] = et;
}
struct UPD {
	int l, r, x, y, v, lca;
}A[M];
struct ASK {
	int tim, x, id;
}B[M], B1[M], B2[M];
struct node {
	int tim, id, op;
}C[M << 1];
void dfs1(int u, int ft) {
	st[u] = ++tmr, fa[u] = ft, dep[u] = dep[ft] + 1, siz[u] = 1;
	for(int i = hed[u]; i; i = e[i].nx) {
		int v = e[i].to; if(v == ft) continue;
		dfs1(v, u), siz[u] += siz[v];
		if(siz[v] > siz[son[u]]) son[u] = v;
	}
	ed[u] = tmr;
}
void dfs2(int u, int tp) {
	top[u] = tp;
	if(son[u]) dfs2(son[u], tp);
	for(int i = hed[u]; i; i = e[i].nx) {
		int v = e[i].to; if(v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
}
inline int LCA(int x, int y) {
	while(top[x] != top[y])
		dep[top[x]] >= dep[top[y]] ? x = fa[top[x]] : y = fa[top[y]];
	return dep[x] < dep[y] ? x : y;
}

inline bool cmp1(const UPD &a, const UPD &b) {
	return a.v < b.v;
}
inline bool cmp2(const node &a,const node &b) {
	return a.tim < b.tim;
}
inline void add(int x, int d) {
	if(!x)return;
	for(int i = x; i <= n; i += i & -i) tr[i] += d; 
}
inline int ask(int x) {
	int res = 0;
	for(int i = x; i > 0; i -= i & -i) res += tr[i];
	return res;
}
inline int ask(int l, int r) {
	return ask(r) - ask(l - 1);
}
void solve(int l, int r, int x, int y) {
	if(x > y) return;
	if(l == r) {
		for(int i = x; i <= y; ++i) ans[B[i].id] = A[l].v;
		return;
	}
	int mid = (l + r) >> 1, tot = 0, t1 = 0, t2 = 0, t = x;
	for(int i = mid + 1; i <= r; ++i)
		C[++tot].tim = A[i].l, C[tot].id = i, C[tot].op = 1,
		C[++tot].tim = A[i].r, C[tot].id = i, C[tot].op = -1;
	for(int i = x; i <= y; ++i)
		C[++tot].tim = B[i].tim, C[tot].id = i, C[tot].op = 0;
	sort(C + 1, C + tot + 1, cmp2);
	for(int i = 1, now = 0; i <= tot; ++i) {
		if(C[i].op) {
			int id = C[i].id, x = A[id].x, y = A[id].y, lca = A[id].lca, o = C[i].op;
			add(st[x], o), add(st[y], o);
			add(st[lca], -o), add(st[fa[lca]], -o), now+= o;
		} else {
			int id = C[i].id, x = B[id].x;
			if(ask(st[x], ed[x]) == now) B1[++t1] = B[id];
			else B2[++t2] = B[id];
		}
	}
	for(int i = 1; i <= t1; ++i) B[t++] = B1[i];
	for(int i = 1; i <= t2; ++i) B[t++] = B2[i];
	solve(l, mid, x, x + t1 - 1), solve(mid + 1, r, x + t1, y);
}
signed main(){
	n = read(), m = read();
	rep(i, 2, n) {
		int x = read(), y = read();
		adde(x, y), adde(y, x);
	}
	dfs1(1, 0), dfs2(1, 1);
	rep(i, 1, m) {
		int opt = read();
		if(opt == 0) {
			int x = read(), y = read(), z = read();
			A[++nu].l = i, A[nu].r = m + 1, A[nu].v = z,
			A[nu].x = x, A[nu].y = y, A[nu].lca = LCA(x, y), id[i] = nu;
		} else if(opt == 1) {
			int x = read(); A[id[x]].r = i;
		} else if(opt == 2) {
			int x = read();
			B[++nq].x = x, B[nq].tim = i, B[nq].id = nq;
		}
	}
	sort(A + 1, A + nu + 1, cmp1), A[0].v = -1;
	solve(0, nu, 1, nq);
	for(int i = 1; i <= nq; ++i) printf("%d\n", ans[i]);
	return 0;
}