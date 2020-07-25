#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=300010;
int n,m;
int dep[N];
int f[N],c[N],a[N];
LL s[N],v[N],h[N];
int ans1[N],ans2[N];
vector<int>g[N];
int tot,root[N];
int ls[N],rs[N],siz[N],fa[N],dst[N];
LL val[N],tg1[N],tg2[N];
void plu(int x,LL d) {val[x]+=d,tg1[x]+=d;}
void mul(int x,LL d) {val[x]*=d,tg1[x]*=d,tg2[x]*=d;}
void pushdown(int x) {
	if(tg2[x]!=1)mul(ls[x],tg2[x]),mul(rs[x],tg2[x]),tg2[x]=1;
	if(tg1[x]!=0)plu(ls[x],tg1[x]),plu(rs[x],tg1[x]),tg1[x]=0;
}
int merge(int x,int y) {
	if(!x||!y)return x|y;
	if(val[x]>val[y])swap(x,y);
	pushdown(x);
	siz[x]+=siz[y],rs[x]=merge(rs[x],y),fa[rs[x]]=x;
	if(dst[ls[x]]<dst[rs[x]])swap(ls[x],rs[x]);
	dst[x]=dst[rs[x]]+1;
	return x;
}
struct Left_Tree {
	int rt;
	Left_Tree(){rt=0;}
	int New(LL x) {
		++tot;
		fa[tot]=tot,tg1[tot]=0,tg2[tot]=1,val[tot]=x,dst[tot]=0,siz[tot]=1;
		return tot;
	}
	void insert(int x) {rt=merge(rt,New(x));}
	int find(int x) {return x==fa[x]?x:fa[x]=find(fa[x]);}
	void pop(int u=0) {
		int x=find(rt);
		ans2[x]=dep[c[x]]-dep[u];
		pushdown(x);
		fa[ls[x]]=ls[x],fa[rs[x]]=rs[x];
		rt=fa[x]=merge(ls[x],rs[x]);
	}
	int root(){return rt=find(rt);}
	LL top(){return val[root()];}
	int size(){return siz[root()];}
	void update1(LL x) {plu(root(),x);}
	void update2(LL x) {mul(root(),x);}
}heap[N];
void dfs(int u) {
	for(uint i=0;i<g[u].size();++i) {
		int v=g[u][i];
		dep[v]=dep[u]+1,dfs(v);
		heap[u].rt=merge(heap[u].root(),heap[v].root());
	}
	while(heap[u].size()&&heap[u].top()<h[u])heap[u].pop(u),++ans1[u];
	a[u]?heap[u].update2(v[u]):heap[u].update1(v[u]);
}
signed main() {
	n=rd(),m=rd();
	for(int i=1;i<=n;++i)scanf("%lld",&h[i]);
	for(int i=2;i<=n;++i)scanf("%d%d%lld",&f[i],&a[i],&v[i]),g[f[i]].pb(i);
	for(int i=1;i<=m;++i)scanf("%lld%d",&s[i],&c[i]),heap[c[i]].insert(s[i]);
	dep[1]=1,dfs(1);
	while(heap[1].size())heap[1].pop(0);
	for(int i=1;i<=n;++i)printf("%d\n",ans1[i]);
	for(int i=1;i<=m;++i)printf("%d\n",ans2[i]);
	return 0;
}