//Orz cyn2006
#include<bits/stdc++.h>
using namespace std;
typedef double db;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
int n,m,q,tot;
namespace Tree{

#define N 20005
int fa[N],top[N],son[N],dep[N],siz[N],dis[N],sum[N];
struct edge{int nxt,to,val;}e[N<<1];
int head[N],num_edge;
void addedge(int fr,int to,int val){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	e[num_edge].val=val;
	head[fr]=num_edge;
}
void dfs1(int u,int ft){
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==ft)continue;
		fa[v]=u,dep[v]=dep[u]+1,dis[v]=dis[u]+e[i].val;
		dfs1(v,u),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp){
	top[u]=tp;
	if(son[u])dfs2(son[u],tp);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
int jump(int u,int anc){
	int res=0;
	while(top[u]!=top[anc])res=top[u],u=fa[top[u]];
	return u==anc?res:son[anc];
}
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int query(int u,int v){
	int lca=LCA(u,v);
	if(lca<=n)return dis[u]+dis[v]-(dis[lca]<<1);
	int x=jump(u,lca),y=jump(v,lca);
	return dis[u]-dis[x]+dis[v]-dis[y]+min(abs(sum[x]-sum[y]),sum[lca]-abs(sum[x]-sum[y]));
}
#undef N

}

namespace cac{

#define N 10005
#define M 20005
using Tree::sum;
int dfn[N],low[N],tmr,val[N],fa[N];
struct edge{int nxt,to,val;}e[M<<1];
int head[N],num_edge;
void addedge(int fr,int to,int val){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	e[num_edge].val=val;
	head[fr]=num_edge;
}
void build(int u,int v,int w){
	int now=v;
	while(now!=fa[u])sum[now]=w,w+=val[now],now=fa[now];
	++tot,sum[tot]=sum[u];
	now=v;
	while(now!=fa[u]){
		int tmp=min(sum[now],sum[tot]-sum[now]);
		Tree::addedge(tot,now,tmp),Tree::addedge(now,tot,tmp);
		now=fa[now];
	}
}
void tarjan(int u,int ft){
	dfn[u]=low[u]=++tmr;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==ft)continue;
		if(!dfn[v])fa[v]=u,val[v]=e[i].val,tarjan(v,u),low[u]=min(low[u],low[v]);
		else low[u]=min(low[u],dfn[v]);
		if(dfn[u]<low[v])Tree::addedge(u,v,e[i].val),Tree::addedge(v,u,e[i].val);
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(fa[v]==u||dfn[v]<=dfn[u])continue;
		build(u,v,e[i].val);
	}
}
#undef N
#undef M

}
signed main(){
	tot=n=read(),m=read(),q=read();
	for(int i=1;i<=m;++i){
		int x=read(),y=read(),z=read();
		cac::addedge(x,y,z),cac::addedge(y,x,z);
	}
	cac::tarjan(1,0),Tree::dfs1(1,0),Tree::dfs2(1,1);
	while(q--){
		int x=read(),y=read();
		printf("%d\n",Tree::query(x,y));
	}
	return 0;
}