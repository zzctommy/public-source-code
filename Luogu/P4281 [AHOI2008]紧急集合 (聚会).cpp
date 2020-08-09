#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=500010;
int n,q;
struct edge {
	int to,nxt;
}e[N<<1];
int head[N],num_edge;
int top[N],fa[N],dep[N],siz[N],son[N];
void addedge(int from,int to) {
	++num_edge;
	e[num_edge].nxt=head[from];
	e[num_edge].to=to;
	head[from]=num_edge;
}
void dfs1(int u,int ft) {
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft)continue;
		dep[v]=dep[u]+1;
		fa[v]=u;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp)  {
	top[u]=tp;
	if(son[u])dfs2(son[u],tp);
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
int LCA(int x,int y) {
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
signed main() {
	n=rd(),q=rd();
	for(int i=1,x,y;i<n;++i)
		x=rd(),y=rd(),addedge(x,y),addedge(y,x);
	dfs1(1,0),dfs2(1,1);
	while(q--) {
		int x=rd(),y=rd(),z=rd(),res=0,mx=-1,tx,ty,tz;
		if(mx<dep[tx=LCA(x,y)])res=tx,mx=dep[tx];
		if(mx<dep[ty=LCA(x,z)])res=ty,mx=dep[ty];
		if(mx<dep[tz=LCA(y,z)])res=tz,mx=dep[tz];
		printf("%d %d\n",res,dep[x]+dep[y]+dep[z]-dep[tx]-dep[ty]-dep[tz]);
	}
	return 0;
}
