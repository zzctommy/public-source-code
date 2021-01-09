#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=1e5+10;
const int M=N*22;
int n,m,a[N],lsh[N],len,lastans;
vector<int>g[N];
int val[M],ls[M],rs[M],root[N],cnt;
int dep[N],fa[N],top[N],son[N],siz[N];
void build(int &p,int l,int r) {
	p=++cnt;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(ls[p],l,mid),build(rs[p],mid+1,r);
}
void update(int pre,int &now,int l,int r,int pos) {
	now=++cnt,ls[now]=ls[pre],rs[now]=rs[pre],val[now]=val[pre]+1;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(pos<=mid)update(ls[pre],ls[now],l,mid,pos);
	else update(rs[pre],rs[now],mid+1,r,pos);
}
int query(int rt1,int rt2,int rt3,int rt4,int l,int r,int k) {
	if(l==r)return lsh[l];
	int sum=val[ls[rt1]]+val[ls[rt2]]-val[ls[rt3]]-val[ls[rt4]],mid=(l+r)>>1;
	if(k<=sum)return query(ls[rt1],ls[rt2],ls[rt3],ls[rt4],l,mid,k);
	else return query(rs[rt1],rs[rt2],rs[rt3],rs[rt4],mid+1,r,k-sum);
} 
void dfs(int u,int ft) {
	update(root[fa[u]],root[u],1,len,a[u]);
	for(uint i=0;i<g[u].size();++i) {
		int v=g[u][i];
		if(v==ft)continue;
		dfs(v,u);
	}
}
void dfs1(int u,int ft) {
	siz[u]=1;
	for(uint i=0;i<g[u].size();++i) {
		int v=g[u][i];
		if(v==ft)continue;
		dep[v]=dep[u]+1,fa[v]=u;
		dfs1(v,u),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp) {
	top[u]=tp;
	if(son[u])dfs2(son[u],tp);
	for(uint i=0;i<g[u].size();++i) {
		int v=g[u][i];
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
	n=rd(),m=rd();
	for(rint i=1;i<=n;++i)lsh[i]=a[i]=rd();
	sort(lsh+1,lsh+n+1),len=unique(lsh+1,lsh+n+1)-lsh-1;
	for(rint i=1;i<=n;++i)a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
	for(rint i=1;i<n;++i) {
		int x=rd(),y=rd();
		g[x].pb(y),g[y].pb(x);
	}
	dfs1(1,0),dfs2(1,1),build(root[1],1,len),dfs(1,0);
	while(m--) {
		int u=rd()^lastans,v=rd(),k=rd(),lca=LCA(u,v);
		printf("%d\n",lastans=query(root[u],root[v],root[lca],root[fa[lca]],1,len,k));
	}
	return 0;
}
