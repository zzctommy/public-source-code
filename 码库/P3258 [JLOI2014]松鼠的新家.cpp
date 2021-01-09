#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=300009;
int n,a[N],dif[N];
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
	for(rint i=head[u];i;i=e[i].nxt) {
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
	for(rint i=head[u];i;i=e[i].nxt) {
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
void dfs(int u,int ft) {
    for(int i=head[u];i;i=e[i].nxt) {
        int v=e[i].to;
        if(v==ft)continue;
        dfs(v,u),dif[u]+=dif[v];
    }
}
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i)a[i]=rd();
	for(rint i=1,x,y;i<n;++i)
		x=rd(),y=rd(),addedge(x,y),addedge(y,x);
	dfs1(1,0),dfs2(1,1);
    for(int i=1;i<n;++i) {
        int u=a[i],v=a[i+1],lca=LCA(u,v);
        ++dif[u],++dif[v],--dif[lca],--dif[fa[lca]];
    }
    dfs(1,0),++dif[a[1]];
    for(int i=1;i<=n;++i)printf("%d\n",dif[i]-1);
	return 0;
}