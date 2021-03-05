#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
typedef long long LL;
typedef long double db;
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
const int M = N;
int n, m, deg[N];
char ans[N];
bool vis[N];
int hed[N], et;
struct edge{int nx, to;} e[M];
inline void adde(int u, int v){
	e[++et].to = v, e[et].nx = hed[u], hed[u] = et;
}
void dfs(int u) {
	for(int i = hed[u]; i; i = e[i].nx) {
		int v = e[i].to;
		if(!vis[v])vis[v] = 1, dfs(v);
	}
}
signed main() {
	n = read(), m = read();
	rep(i, 1, m) {
		int x = read(), y = read();
		adde(y, x), ++deg[y];
	}
	dfs(1);
	for(int i = 1; i <= n; ++i) ans[i] = vis[i] ? '1' : '0';
	if(!deg[1]) ans[1] = '1';
	ans[n + 1] = '\0';
	puts(ans + 1);
}