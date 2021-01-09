#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100009;
int n,q,v[N];
struct edge {
	int to,nxt;
}e[N<<1];
int head[N],num_edge;
int top[N],fa[N],dfn[N],timer,dep[N],siz[N],son[N];
namespace BIT {
	int tr[N];
	#define lt(i) (i&(-i))
	void add(int x,int d) {for(int i=x;i<=n;i+=lt(i))tr[i]^=d;}
	int ask(int x) {
		int res=0;
		for(int i=x;i>0;i-=lt(i))res^=tr[i];
		return res;
	}
	int ask(int l,int r) {
		return ask(r)^ask(l-1);
	}
}
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
	dfn[u]=++timer;
	if(son[u])dfs2(son[u],tp);
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
int query(int x,int y) {
	int res=0;
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
		res^=BIT::ask(dfn[top[x]],dfn[x]),x=fa[top[x]];
	}
	if(dfn[x]>dfn[y])x^=y^=x^=y;
	res^=BIT::ask(dfn[x],dfn[y]);
	return res;
}
signed main() {
	n=rd(),q=rd();
	for(int i=1;i<=n;++i)v[i]=rd();
	for(int i=1,x,y;i<n;++i)
		x=rd(),y=rd(),addedge(x,y),addedge(y,x);
	dep[1]=1,dfs1(1,0),dfs2(1,1);
	for(int i=1;i<=n;++i)BIT::add(dfn[i],v[i]);
	while(q--) {
		int opt=rd(),x=rd(),y=rd();
		if(opt==1)BIT::add(dfn[x],y^v[x]),v[x]=y;
		else printf("%d\n",query(x,y));
	} 
	return 0;
}