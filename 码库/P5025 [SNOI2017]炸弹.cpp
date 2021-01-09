#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=500010;
const int M=N<<2;
const int mod=1e9+7;
int n,pos[N],ans;
LL x[N],r[N];
int lp[M],rp[M],Lp[M],Rp[M];
int head[M],num_edge;
int dfn[M],low[M],timer,st[M],top,C,scc[M];
int ind[M],numnode;
struct edge {
	int nxt,to;
}e[N*25];
vector<int>g[M];
void addedge(int from,int to) {
	++num_edge;
	e[num_edge].nxt=head[from];
	e[num_edge].to=to;
	head[from]=num_edge;
}
#define lc (p<<1)
#define rc (p<<1|1)
void build(int l,int r,int p) {
	lp[p]=l,rp[p]=r,numnode=max(numnode,p);
	if(l==r)return void(pos[l]=p);
	int mid=(l+r)>>1;
	addedge(p,lc),addedge(p,rc);
	build(l,mid,lc),build(mid+1,r,rc);
}
void update(int ql,int qr,int l,int r,int p,int k) {
	if(ql<=l&&r<=qr) {
		addedge(k,p);return;
	}
	int mid=(l+r)>>1;
	if(mid>=ql)update(ql,qr,l,mid,lc,k);
	if(mid<qr)update(ql,qr,mid+1,r,rc,k);
}
void tarjan(int u) {
	dfn[u]=low[u]=++timer,st[++top]=u;
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
		else if(!scc[v])low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]) {
		scc[u]=++C,Lp[C]=lp[u],Rp[C]=rp[u];
		while(st[top]!=u)scc[st[top]]=C,Lp[C]=min(Lp[C],lp[st[top]]),Rp[C]=max(Rp[C],rp[st[top]]),--top;
		--top;
	} 
}
void buildDAG() {
	for(rint u=1;u<=numnode;++u) {
		for(rint i=head[u];i;i=e[i].nxt) {
			int v=e[i].to;
			if(scc[u]!=scc[v])g[scc[v]].pb(scc[u]),++ind[scc[u]];
		}
	}
}
void topo() {
	queue<int>q;
	for(rint i=1;i<=C;++i)if(!ind[i])q.push(i);
	while(!q.empty()) {
		int u=q.front();q.pop();
		for(uint i=0;i<g[u].size();++i) {
			int v=g[u][i];
			Lp[v]=min(Lp[v],Lp[u]);
			Rp[v]=max(Rp[v],Rp[u]);
			--ind[v];
			if(!ind[v])q.push(v);
		}
	}
}
signed main() {
	n=rd();build(1,n,1);
	for(rint i=1;i<=n;++i)x[i]=rd(),r[i]=rd();
	for(rint i=1;i<=n;++i) {
		int lp=lower_bound(x+1,x+i+1,x[i]-r[i])-x;
		int rp=upper_bound(x+i,x+n+1,x[i]+r[i])-x-1;
		update(lp,rp,1,n,1,pos[i]);
	}
	tarjan(1),buildDAG(),topo();
	for(rint i=1;i<=n;++i)ans=(ans+(Rp[scc[pos[i]]]-Lp[scc[pos[i]]]+1)*i)%mod;
	printf("%lld\n",ans);
	return 0;
}