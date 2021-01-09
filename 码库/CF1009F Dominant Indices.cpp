#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=1000010;
const int M=21*N;
const int inf=1000000007;
int n,ans[N];
int dep[N];
int head[N],num_edge;
int root[N],tot,ls[M],rs[M],val[M],id[M];
struct edge {
	int nxt,to;
}e[N<<1];
void addedge(int fr,int to) {
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
void pushup(int p) {
	val[p]=0;
	if(val[p]<val[ls[p]])val[p]=val[ls[p]],id[p]=id[ls[p]];
	if(val[p]<val[rs[p]])val[p]=val[rs[p]],id[p]=id[rs[p]];
}
void update(int &p,int l,int r,int pos,int k) {
	if(!p)p=++tot;
	if(l==r){val[p]+=k,id[p]=l;return;}
	int mid=(l+r)>>1;
	if(pos<=mid)update(ls[p],l,mid,pos,k);
	else update(rs[p],mid+1,r,pos,k);
	pushup(p);
}
int merge(int x,int y,int l,int r) {
	if(!x||!y)return x|y;
	int mid=(l+r)>>1;
	if(l==r){val[x]+=val[y];return x;}
	ls[x]=merge(ls[x],ls[y],l,mid);
	rs[x]=merge(rs[x],rs[y],mid+1,r);
	pushup(x);return x;
}
void dfs(int u,int ft) {
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft)continue;
		dep[v]=dep[u]+1;
		dfs(v,u);
		root[u]=merge(root[u],root[v],1,n); 
	}
	update(root[u],1,n,dep[u],1);
	ans[u]=id[root[u]]-dep[u];
}
signed main() {
	n=rd();
	for(int i=1;i<n;++i) {
		int x=rd(),y=rd();
		addedge(x,y),addedge(y,x);
	}
	dep[1]=1,dfs(1,0);
	for(int i=1;i<=n;++i)printf("%d\n",ans[i]);
	return 0;
}
