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

const int N = 2005 * 4;
const int M = 10 * 2005 * 2;
const int inf = 0x3f3f3f3f;
int n, m, cnt;
int mf, mc, S, T, ND, hed[N], et = 1;
int dis[N], cur[N];
bool inq[N], vis[N];
vector <vector<int> >mp;
int id(int i,int j,int d) { return (d - 1) * n * m + (i - 1) * m + j; }
struct edge {int nx, to, fl, c;}e[M];
inline void addedge(int u, int v, int fl, int c) {
	e[++et].nx = hed[u], e[et].to = v, e[et].fl = fl, e[et].c = c, hed[u] = et;
}
inline void adde(int u, int v, int fl, int c) {
	addedge(u, v, fl, c), addedge(v, u, 0, -c);
}
bool spfa() {
	queue <int> q;
	for(int i = 1; i <= ND; ++i) inq[i] = 0, dis[i] = inf, cur[i] = hed[i];
	q.push(S), dis[S] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop(), inq[u] = 0;
		for(int i = hed[u]; i; i = e[i].nx) {
			int v = e[i].to;
			if(e[i].fl && ckmin(dis[v], dis[u] + e[i].c)) {
				if(!inq[v]) q.push(v), inq[v] = 1;
			}
		}
	}
	return dis[T] < inf; 
}
int dfs(int u, int fl) {
	vis[u] = 1;
	if(u == T) return fl;
	int rl, us = 0;
	for(int i = cur[u]; i; i = e[i].nx) {
		int v = e[i].to; cur[u] = i;
		if(dis[v] == dis[u] + e[i].c && e[i].fl && (v == T || !vis[v])) {
			rl = dfs(v, min(fl - us, e[i].fl));
			if(rl) e[i].fl -= rl, e[i ^ 1].fl += rl, mc += e[i].c * rl, us += rl;
			if(us == fl)break;
		}
	}
	return us;
}
void MCMF(){
	mc = mf = 0;
	while(spfa()) {
		vis[T] = 1;
		while(vis[T]) 
			memset(vis, 0, T + 1), mf += dfs(S, inf);
	}
}
signed main() {
	n = read(), m = read(), mp.resize(n + 1);
	S = n * m * 4 + 1, T = S + 1, ND = T;
	for(int i = 1; i <= n; ++i){
		mp[i].resize(m + 1);
		for(int j = 1; j <= m; ++j) mp[i][j] = read();
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			if((i + j) & 1) {
				if(i > 1) adde(id(i, j, 1), id(i - 1, j, 3), 1, 0);
				if(j < m) adde(id(i, j, 2), id(i, j + 1, 4), 1, 0);
				if(i < n) adde(id(i, j, 3), id(i + 1, j, 1), 1, 0);
				if(j > 1) adde(id(i, j, 4), id(i, j - 1, 2), 1, 0);
			}
			if(mp[i][j] == 1) {//U
				cnt += 1;
				if((i + j) & 1) {
					adde(S, id(i, j, 1), 1, 0);
					adde(id(i, j, 1), id(i, j, 2), 1, 1);
					adde(id(i, j, 1), id(i, j, 3), 1, 2);
					adde(id(i, j, 1), id(i, j, 4), 1, 1);
				} else {
					adde(id(i, j, 1), T, 1, 0);
					adde(id(i, j, 2), id(i, j, 1), 1, 1);
					adde(id(i, j, 3), id(i, j, 1), 1, 2);
					adde(id(i, j, 4), id(i, j, 1), 1, 1);
				}
			} else if(mp[i][j] == 2) {//R
				cnt += 1;
				if((i + j) & 1) {
					adde(S, id(i, j, 2), 1, 0);
					adde(id(i, j, 2), id(i, j, 1), 1, 1);
					adde(id(i, j, 2), id(i, j, 3), 1, 1);
					adde(id(i, j, 2), id(i, j, 4), 1, 2);
				} else {
					adde(id(i, j, 2), T, 1, 0);
					adde(id(i, j, 1), id(i, j, 2), 1, 1);
					adde(id(i, j, 3), id(i, j, 2), 1, 1);
					adde(id(i, j, 4), id(i, j, 2), 1, 2);
				}
			} else if(mp[i][j] == 4) {//D
				cnt += 1;
				if((i + j) & 1) {
					adde(S, id(i, j, 3), 1, 0);
					adde(id(i, j, 3), id(i, j, 1), 1, 2);
					adde(id(i, j, 3), id(i, j, 2), 1, 1);
					adde(id(i, j, 3), id(i, j, 4), 1, 1);
				} else {
					adde(id(i, j, 3), T, 1, 0);
					adde(id(i, j, 1), id(i, j, 3), 1, 2);
					adde(id(i, j, 2), id(i, j, 3), 1, 1);
					adde(id(i, j, 4), id(i, j, 3), 1, 1);
				}
			} else if(mp[i][j] == 8) {//L
				cnt += 1;
				if((i + j) & 1) {
					adde(S, id(i, j, 4), 1, 0);
					adde(id(i, j, 4), id(i, j, 1), 1, 1);
					adde(id(i, j, 4), id(i, j, 2), 1, 2);
					adde(id(i, j, 4), id(i, j, 3), 1, 1);
				} else {
					adde(id(i, j, 4), T, 1, 0);
					adde(id(i, j, 1), id(i, j, 4), 1, 1);
					adde(id(i, j, 2), id(i, j, 4), 1, 2);
					adde(id(i, j, 3), id(i, j, 4), 1, 1);
				}
			} else if(mp[i][j] == 3) {//UR
				cnt += 2;
				if((i + j) & 1) {
					adde(S, id(i, j, 1), 1, 0);
					adde(S, id(i, j, 2), 1, 0);
					adde(id(i, j, 1), id(i, j, 3), 1, 1);
					adde(id(i, j, 2), id(i, j, 4), 1, 1);
				} else {
					adde(id(i, j, 1), T, 1, 0);
					adde(id(i, j, 2), T, 1, 0);
					adde(id(i, j, 3), id(i, j, 1), 1, 1);
					adde(id(i, j, 4), id(i, j, 2), 1, 1);
				}
			} else if(mp[i][j] == 6) {//RD
				cnt += 2;
				if((i + j) & 1) {
					adde(S, id(i, j, 2), 1, 0);
					adde(S, id(i, j, 3), 1, 0);
					adde(id(i, j, 2), id(i, j, 4), 1, 1);
					adde(id(i, j, 3), id(i, j, 1), 1, 1);
				} else {
					adde(id(i, j, 2), T, 1, 0);
					adde(id(i, j, 3), T, 1, 0);
					adde(id(i, j, 4), id(i, j, 2), 1, 1);
					adde(id(i, j, 1), id(i, j, 3), 1, 1);
				}
			} else if(mp[i][j] == 12) {//DL
				cnt += 2;
				if((i + j) & 1) {
					adde(S, id(i, j, 3), 1, 0);
					adde(S, id(i, j, 4), 1, 0);
					adde(id(i, j, 3), id(i, j, 1), 1, 1);
					adde(id(i, j, 4), id(i, j, 2), 1, 1);
				} else {
					adde(id(i, j, 3), T, 1, 0);
					adde(id(i, j, 4), T, 1, 0);
					adde(id(i, j, 1), id(i, j, 3), 1, 1);
					adde(id(i, j, 2), id(i, j, 4), 1, 1);
				}
			} else if(mp[i][j] == 9) {//LU
				cnt += 2;
				if((i + j) & 1) {
					adde(S, id(i, j, 4), 1, 0);
					adde(S, id(i, j, 1), 1, 0);
					adde(id(i, j, 4), id(i, j, 2), 1, 1);
					adde(id(i, j, 1), id(i, j, 3), 1, 1);
				} else {
					adde(id(i, j, 4), T, 1, 0);
					adde(id(i, j, 1), T, 1, 0);
					adde(id(i, j, 2), id(i, j, 4), 1, 1);
					adde(id(i, j, 3), id(i, j, 1), 1, 1);
				}
			} else if(mp[i][j] == 5) {//DU
				cnt += 2;
				if((i + j) & 1) {
					adde(S, id(i, j, 1), 1, 0);
					adde(S, id(i, j, 3), 1, 0);
				} else {
					adde(id(i, j, 1), T, 1, 0);
					adde(id(i, j ,3), T, 1, 0);
				}
			} else if(mp[i][j] == 10) {//LR
				cnt += 2;
				if((i + j) & 1) {
					adde(S, id(i, j, 2), 1, 0);
					adde(S, id(i, j, 4), 1, 0);
				} else {
					adde(id(i, j, 2), T, 1, 0);
					adde(id(i, j, 4), T, 1, 0);
				}
			} else if(mp[i][j] == 7) {//URD
				cnt += 3;
				if((i + j) & 1) {
					adde(S, id(i, j, 1), 1, 0);
					adde(S, id(i, j, 2), 1, 0);
					adde(S, id(i, j, 3), 1, 0);
					adde(id(i, j, 1), id(i, j, 4), 1, 1);
					adde(id(i, j, 2), id(i, j, 4), 1, 2);
					adde(id(i, j, 3), id(i, j, 4), 1, 1);
				} else {
					adde(id(i, j, 1), T, 1, 0);
					adde(id(i, j, 2), T, 1, 0);
					adde(id(i, j, 3), T, 1, 0);
					adde(id(i, j, 4), id(i, j, 1), 1, 1);
					adde(id(i, j, 4), id(i, j, 2), 1, 2);
					adde(id(i, j, 4), id(i, j, 3), 1, 1);
				}
			} else if(mp[i][j] == 11) {//URL
				cnt += 3;
				if((i + j) & 1) {
					adde(S, id(i, j, 1), 1, 0);
					adde(S, id(i, j, 2), 1, 0);
					adde(S, id(i, j, 4), 1, 0);
					adde(id(i, j, 1), id(i, j, 3), 1, 2);
					adde(id(i, j, 2), id(i, j, 3), 1, 1);
					adde(id(i, j, 4), id(i, j, 3), 1, 1);
				} else {
					adde(id(i, j, 1), T, 1, 0);
					adde(id(i, j, 2), T, 1, 0);
					adde(id(i, j, 4), T, 1, 0);
					adde(id(i, j, 3), id(i, j, 1), 1, 2);
					adde(id(i, j, 3), id(i, j, 2), 1, 1);
					adde(id(i, j, 3), id(i, j, 4), 1, 1);
				}
			} else if(mp[i][j] == 13) {//UDL
				cnt += 3;
				if((i + j) & 1) {
					adde(S, id(i, j, 1), 1, 0);
					adde(S, id(i, j, 3), 1, 0);
					adde(S, id(i, j, 4), 1, 0);
					adde(id(i, j, 1), id(i, j, 2), 1, 1);
					adde(id(i, j, 3), id(i, j, 2), 1, 1);
					adde(id(i, j, 4), id(i, j, 2), 1, 2);
				} else {
					adde(id(i, j, 1), T, 1, 0);
					adde(id(i, j, 3), T, 1, 0);
					adde(id(i, j, 4), T, 1, 0);
					adde(id(i, j, 2), id(i, j, 1), 1, 1);
					adde(id(i, j, 2), id(i, j, 3), 1, 1);
					adde(id(i, j, 2), id(i, j, 4), 1, 2);
				}
			} else if(mp[i][j] == 14) {//LDR
				cnt += 3;
				if((i + j) & 1) {
					adde(S, id(i, j, 2), 1, 0);
					adde(S, id(i, j, 3), 1, 0);
					adde(S, id(i, j, 4), 1, 0);
					adde(id(i, j, 2), id(i, j, 1), 1, 1);
					adde(id(i, j, 3), id(i, j, 1), 1, 2);
					adde(id(i, j, 4), id(i, j, 1), 1, 1);
				} else {
					adde(id(i, j, 2), T, 1, 0);
					adde(id(i, j, 3), T, 1, 0);
					adde(id(i, j, 4), T, 1, 0);
					adde(id(i, j, 1), id(i, j, 2), 1, 1);
					adde(id(i, j, 1), id(i, j, 3), 1, 2);
					adde(id(i, j, 1), id(i, j, 4), 1, 1);
				}
			} else if(mp[i][j] == 15) {//URDL
				cnt += 4;
				if((i + j) & 1) {
					adde(S, id(i, j, 1), 1, 0);
					adde(S, id(i, j, 2), 1, 0);
					adde(S, id(i, j, 3), 1, 0);
					adde(S, id(i, j, 4), 1, 0);
				} else {
					adde(id(i, j, 1), T, 1, 0);
					adde(id(i, j, 2), T, 1, 0);
					adde(id(i, j, 3), T, 1, 0);
					adde(id(i, j, 4), T, 1, 0);
				}
			}
		}
	}
	MCMF();
	if(mf * 2 != cnt) puts("-1");
	else cout << mc << endl;
	return 0;
}