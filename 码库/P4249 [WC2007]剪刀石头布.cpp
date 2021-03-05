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

const int N = 105 * 105 / 2 + 105;
const int M = (3 * 105 * 105 / 2 + 105 * 105) * 2;
const int inf = 0x3f3f3f3f;
int n, a[105][105];
pair <int, int> b[105 * 105];
int dis[N], cur[N], S, T, ND, mf, mc;
bool inq[N], vis[N];
int hed[N], et = 1;
struct edge{ int nx, to, fl, c; } e[M];
inline void Adde(int u, int v, int fl, int c) {
	e[++et].nx = hed[u], e[et].to = v, e[et].fl = fl, e[et].c = c, hed[u] = et;
}
inline void adde(int u, int v, int fl, int c) {
	Adde(u, v, fl, c), Adde(v, u, 0, -c);
}
bool spfa() {
	queue <int> q;
	for(int i = 1; i <= ND; ++i)
		cur[i] = hed[i], dis[i] = inf;
	q.push(S), dis[S] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop(), inq[u] = 0;
		for(int i = hed[u]; i; i = e[i].nx) {
			int v = e[i].to;
			if(e[i].fl && ckmin(dis[v], dis[u] + e[i].c)) {
				if (!inq[v]) inq[v] = 1, q.push(v);
			}
		}
	}
	return dis[T] < T;
}
int dfs(int u, int fl) {
	vis[u] = 1;
	if(u == T) return fl;
	int us = 0, rl;
	for(int i = cur[u]; i; i = e[i].nx) {
		int v = e[i].to; cur[u] = i;
		if(e[i].fl && dis[v] == dis[u] + e[i].c && (v == T || !vis[v])) {
			rl = dfs(v, min(fl - us, e[i].fl));
			if(rl) e[i].fl -= rl, e[i ^ 1].fl += rl, mc += e[i].c * rl, us += rl;
			if(us == fl) break;
		}
	}
	return us;
}
void MCMF() {
	while(spfa()){
		vis[T] = 1;
		while(vis[T]) memset(vis, 0, T + 1), mf += dfs(S, inf);
	}
}
signed main() {
	n = read();
	rep(i, 1, n) rep(j, 1, n) a[i][j] = read();
	S = n * (n - 1) / 2 + n + 1, T = S + 1, ND = T;
	int idx = 0;
	rep(i, 1, n) {
		rep(j, 1, i - 1) {
			++idx, b[idx] = mkp(i, j);
			adde(S, idx + n, 1, 0);
			if(a[i][j] == 2) {
				adde(idx + n, i, 1, 0);
				adde(idx + n, j, 1, 0);
			} else if(a[i][j] == 1) {
				adde(idx + n, j, 1, 0);
			} else adde(idx + n, i, 1, 0);
			
		}
	}
	rep(i, 1, n)
		rep(j, 0, n - 1) adde(i, T, 1, j);
	MCMF();
	printf("%d\n", n * (n - 1) * (n - 2) / 6 - mc);
	memset(a, 0, sizeof(a));
	for(int i = 2; i <= et; i += 2) {
		int u = e[i ^ 1].to, v = e[i].to;
		if(u == S || v == T || v == S || u == T) continue;
		if(e[i ^ 1].fl) {
			int x = b[u - n].fi, y = b[u - n].se;
			if(x == v) a[y][v] = 1, a[v][y] = 0;
			else a[x][v] = 1, a[v][x] = 0;
		}
	}
	rep(i, 1, n) {
		rep(j, 1, n) printf("%d ",a[i][j]);
		puts("");
	}
}