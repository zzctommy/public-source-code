#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(a) push_back(a)
#define mkp(a,y) make_pair(a,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int a=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))a=a*10+(ch^48),ch=getchar();
    return a*f;
}
#define N 100009
int n,m,a[N];
int dfn[N],top[N],fa[N],siz[N],son[N],dep[N],timer;
vector<int>g[N];
set<int>v[N];
struct ASK {
	int x,y,z;
}q[N<<1];
void dfs1(int u,int ft) {
	siz[u]=1;
	for(int v:g[u]) {
		if(v==ft)continue;
		fa[v]=u,dep[v]=dep[u]+1,dfs1(v,u),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp) {
	top[u]=tp,dfn[u]=++timer;
	if(son[u])dfs2(son[u],tp);
	for(int v:g[u]) {
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
int query(int x,int y,int z) {
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
		if(*v[z].lower_bound(dfn[top[x]])<=dfn[x])return 1;
		x=fa[top[x]];
	}
	if(dfn[x]>dfn[y])x^=y^=x^=y;
	return *v[z].lower_bound(dfn[x])<=dfn[y];
}
void Main() {
	for(int i=0;i<=n;++i)g[i].clear(),v[i].clear();
	memset(son,0,sizeof(son));
	memset(dfn,0,sizeof(dfn));
	memset(top,0,sizeof(top));
	memset(fa,0,sizeof(fa));
	memset(siz,0,sizeof(siz));
	memset(dep,0,sizeof(dep));
	timer=0;
	for(int i=1;i<=n;++i)a[i]=rd();
	for(int i=1;i<n;++i) {
		int x=rd(),y=rd();
		g[x].pb(y),g[y].pb(x);
	}
	for(int i=1;i<=m;++i)q[i].x=rd(),q[i].y=rd(),q[i].z=rd();
	for(int i=0;i<=n;++i)v[i].insert(0),v[i].insert(n+1);
	dfs1(1,0),dfs2(1,1);
	for(int i=1;i<=n;++i)v[a[i]].insert(dfn[i]);
	for(int i=1;i<=m;++i)puts(query(q[i].x,q[i].y,q[i].z)?"Find":"NotFind");
}
signed main() {
	while(scanf("%d%d",&n,&m)!=EOF)Main();
}