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
#define int long long
#define N 100009
int n,m,root=1;
int st[N],rev[N],top[N],fa[N],siz[N],son[N],dep[N],a[N],ed[N],timer;
int val[N<<2],tag[N<<2];
vector<int>g[N];
void dfs1(int u,int ft) {
	siz[u]=1;
	for(int v:g[u]) {
		if(v==ft)continue;
		fa[v]=u,dep[v]=dep[u]+1,dfs1(v,u),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp) {
	top[u]=tp,st[u]=++timer,rev[timer]=u;
	if(son[u])dfs2(son[u],tp);
	for(int v:g[u]) {
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
	ed[u]=timer;
}
int LCA(int x,int y) {
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int findnex(int u,int f) {
	int res=0;
	while(top[u]!=top[f])u=fa[res=top[u]];
	return u==f?res:son[f];
}
#define lc (p<<1)
#define rc (p<<1|1)
void pushup(int p) {val[p]=val[lc]+val[rc];}
void build(int l,int r,int p) {
	if(l==r)return val[p]=a[rev[l]],void();
	int mid=(l+r)>>1;
	build(l,mid,lc),build(mid+1,r,rc);
	pushup(p);
}
void pushdown(int p,int l,int r) {
	if(tag[p]) {
		int mid=(l+r)>>1;
		tag[lc]+=tag[p],val[lc]+=tag[p]*(mid-l+1);
		tag[rc]+=tag[p],val[rc]+=tag[p]*(r-mid);
		tag[p]=0;
	}
}
void update(int ql,int qr,int l,int r,int k,int p) {
	if(ql<=l&&r<=qr)return tag[p]+=k,val[p]+=k*(r-l+1),void();
	pushdown(p,l,r);
	int mid=(l+r)>>1;
	if(ql<=mid)update(ql,qr,l,mid,k,lc);
	if(qr>mid)update(ql,qr,mid+1,r,k,rc);
	pushup(p);
}
int query(int ql,int qr,int l,int r,int p) {
	if(ql<=l&&r<=qr)return val[p];
	int mid=(l+r)>>1,res=0;
	pushdown(p,l,r);
	if(ql<=mid)res+=query(ql,qr,l,mid,lc);
	if(qr>mid)res+=query(ql,qr,mid+1,r,rc);
	return res;
}
void modify(int x,int z) {
	if(x==root)update(1,n,1,n,z,1);
	else {
		int lca=LCA(root,x);
		if(lca!=x)update(st[x],ed[x],1,n,z,1);
		else {
			int t=findnex(root,x);
			if(st[t]!=1)update(1,st[t]-1,1,n,z,1);
			if(ed[t]!=n)update(ed[t]+1,n,1,n,z,1);
		}
	}
}
int ask(int x) {
	if(x==root)return query(1,n,1,n,1);
	else {
		int lca=LCA(root,x);
		if(lca!=x)return query(st[x],ed[x],1,n,1);
		else {
			int t=findnex(root,x),res=0;
			if(st[t]!=1)res+=query(1,st[t]-1,1,n,1);
			if(ed[t]!=n)res+=query(ed[t]+1,n,1,n,1);
			return res;
		}
	}
}
int dis(int x,int y){return dep[x]+dep[y]-(dep[LCA(x,y)]<<1);}
int LCA_ex(int x,int y) {
	int f=LCA(x,y),g=LCA(x,root),h=LCA(y,root),res=f;
	if(dep[g]>dep[res])res=g;
	if(dep[h]>dep[res])res=h;
	return res;
}
signed main() {
	n=rd(),m=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	for(int i=1;i<n;++i) {
		int x=rd(),y=rd();
		g[x].pb(y),g[y].pb(x);
	}
	dfs1(1,0),dfs2(1,1),build(1,n,1);
	while(m--) {
		int opt=rd(),x=rd(),y,z;
		if(opt==1)root=x;
		else if(opt==2)y=rd(),z=rd(),modify(LCA_ex(x,y),z);
		else printf("%lld\n",ask(x));
	}
	return 0;
}