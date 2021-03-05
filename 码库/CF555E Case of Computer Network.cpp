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

const int N=200005;
const int M=N<<1;
int n,m,q,ans=1;
int hed[N],et=1;
struct edge{int nx,to;}e[M];
inline void adde(int u,int v){e[++et].to=v,e[et].nx=hed[u],hed[u]=et;}
int dfn[N],low[N],tmr,bel[N],D;
int col[N],C;
bool bri[M];
vector<int>g[N];
int bz[20][N],dep[N],df0[N],df1[N];

void tarjan(int u,int ft){
	dfn[u]=low[u]=++tmr,bel[u]=D;
	bool flg=0;
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;
		if(v==ft&&!flg){flg=1;continue;}
		if(!dfn[v]){
			tarjan(v,u),ckmin(low[u],low[v]);
			if(low[v]>dfn[u])bri[i]=bri[i^1]=1;
		}else ckmin(low[u],dfn[v]);
	}
}
void dfsc(int u){
	if(col[u])return;
	col[u]=C;
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;
		if(!bri[i])dfsc(v);
		else {
			if(col[v])g[col[u]].pb(col[v]),g[col[v]].pb(col[u]);
		}
	}
}
void dfs1(int u,int ft){
	dep[u]=dep[bz[0][u]=ft]+1;
	for(int i=1;1<<i<dep[u];++i)bz[i][u]=bz[i-1][bz[i-1][u]];
	for(int v:g[u]){
		if(v==ft)continue;
		dfs1(v,u);
	}
}
inline int LCA(int x,int y){
	if(dep[x]<dep[y])x^=y^=x^=y;
	for(int i=0,j=dep[x]-dep[y];i<=19;++i)
		if(j>>i&1)x=bz[i][x];
	if(x==y)return x;
	for(int i=19;i>=0;--i)
		if(bz[i][x]!=bz[i][y])x=bz[i][x],y=bz[i][y];
	return bz[0][x];
}
void dfs2(int u,int ft){
	for(int v:g[u]){
		if(v==ft)continue;
		dfs2(v,u);
		df0[u]+=df0[v],df1[u]+=df1[v];
	}
	if(u!=1)ans&=!df0[u]||!df1[u];
}
signed main(){
	n=read(),m=read(),q=read();
	rep(i,1,m){
		int x=read(),y=read();
		adde(x,y),adde(y,x);
	}
	rep(i,1,n)if(!dfn[i])++D,tarjan(i,0);
	rep(i,1,n)if(!col[i])++C,dfsc(i);
	rep(i,1,C)sort(g[i].begin(),g[i].end()),
		g[i].resize(unique(g[i].begin(),g[i].end())-g[i].begin());
	rep(i,1,n)if(!dep[i])dfs1(i,0);
	rep(i,1,q){
		int x=read(),y=read();
		if(bel[x]!=bel[y])return puts("No")&0;
		if(col[x]==col[y])continue;
		int lca=LCA(col[x],col[y]);
		++df0[col[x]],--df0[lca];
		++df1[col[y]],--df1[lca];
	}
	rep(i,1,n)if(dep[i]==1)dfs2(i,0);
	puts(ans?"Yes":"No");
	return 0;
}