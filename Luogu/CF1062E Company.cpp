#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define fi first
#define se second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 100005
int n,q,fa[N],mi[18][N],mx[18][N],lca[18][N],lg[N],pw2[30];
int siz[N],son[N],dep[N],top[N],dfn[N],tmr;
struct edge{int nxt,to;}e[N];
int head[N],num_edge;
void addedge(int fr,int to){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
void dfs1(int u,int ft){
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		dep[v]=dep[u]+1,dfs1(v,u),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp){
	top[u]=tp,dfn[u]=++tmr;
	if(son[u])dfs2(son[u],tp);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
int LCA(int x,int y){
	if(!x||!y)return x|y;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int ask_min(int l,int r){
	int x=lg[r-l+1],t=r-pw2[x]+1;
	return dfn[mi[x][l]]<dfn[mi[x][t]]?mi[x][l]:mi[x][t];
}
int ask_max(int l,int r){
	int x=lg[r-l+1],t=r-pw2[x]+1;
	return dfn[mx[x][l]]<dfn[mx[x][t]]?mx[x][t]:mx[x][l];
}
int ask_LCA(int l,int r){
	if(l>r)return 0;
	int x=lg[r-l+1],t=r-pw2[x]+1;
	return LCA(lca[x][l],lca[x][t]);
}
signed main(){
	n=read(),q=read();
	for(int i=2;i<=n;++i)addedge(fa[i]=read(),i);
	dfs1(1,0),dfs2(1,1);
	pw2[0]=1;for(int i=1;i<=20;++i)pw2[i]=pw2[i-1]<<1;
	lg[0]=-1;for(int i=1;i<=n;++i)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;++i)mx[0][i]=mi[0][i]=lca[0][i]=i;
	for(int i=1;i<=lg[n];++i)
		for(int j=1;j+pw2[i]-1<=n;++j){
			int t=j+pw2[i-1];
			if(dfn[mx[i-1][j]]<dfn[mx[i-1][t]])mx[i][j]=mx[i-1][t];
			else mx[i][j]=mx[i-1][j];
			if(dfn[mi[i-1][j]]<dfn[mi[i-1][t]])mi[i][j]=mi[i-1][j];
			else mi[i][j]=mi[i-1][t];
			lca[i][j]=LCA(lca[i-1][j],lca[i-1][t]);
		}
	while(q--){
		int l=read(),r=read(),p=lg[r-l+1],t=r-pw2[p]+1;
		int idx=ask_min(l,r),idy=ask_max(l,r);
		int x=LCA(ask_LCA(l,idx-1),ask_LCA(idx+1,r)),y=LCA(ask_LCA(l,idy-1),ask_LCA(idy+1,r));
		dep[x]>dep[y]?printf("%d %d\n",idx,dep[x]):printf("%d %d\n",idy,dep[y]);
	}
	return 0;
}