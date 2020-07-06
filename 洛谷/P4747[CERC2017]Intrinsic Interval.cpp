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
const int N=100010;
const int D=N<<2;
const int M=N*25;
int n,m,a[N],pos[N];
int bin[18],lg[N];
int lp[D],rp[D],Lp[D],Rp[D],ind[D];
int sta[D],timer,top,dfn[D],low[D],scc[D],C;
int maxpos;         
struct ST_table {
	int st_max[18][N],st_min[18][N],n;
	void init() {
		for(rint i=1;i<=lg[n];++i)
			for(rint j=1;j+bin[i]-1<=n;++j)
				st_max[i][j]=max(st_max[i-1][j],st_max[i-1][j+bin[i-1]]),
				st_min[i][j]=min(st_min[i-1][j],st_min[i-1][j+bin[i-1]]);
	}
	int query_max(int l,int r) {
		if(l>r)l^=r^=l^=r;
		int x=lg[r-l+1];
		return max(st_max[x][l],st_max[x][r-bin[x]+1]);
	}
	int query_min(int l,int r) {
		if(l>r)l^=r^=l^=r;
		int x=lg[r-l+1];
		return min(st_min[x][l],st_min[x][r-bin[x]+1]);
	}
}st[2];
struct graph {
	int nxt[M],head[M],to[M],num_edge;
	graph(){num_edge=0;}
	void addedge(int u,int v) {
		++num_edge;
		to[num_edge]=v;
		nxt[num_edge]=head[u];
		head[u]=num_edge;
	}
}g,dag;
struct Segment_Tree {
	#define lc p<<1
	#define rc p<<1|1
	void build(int l,int r,int p) {
		maxpos=max(maxpos,p);
		if(l==r)return void(pos[l]=p);
		int mid=(l+r)>>1;
		g.addedge(p,lc),g.addedge(p,rc);
		build(l,mid,lc),build(mid+1,r,rc);
	}
	void update(int ql,int qr,int l,int r,int p,int k) {
		if(ql<=l&&r<=qr) {g.addedge(k,p);return;}
		int mid=(l+r)>>1;
		if(mid>=ql)update(ql,qr,l,mid,lc,k);
		if(mid<qr)update(ql,qr,mid+1,r,rc,k);
	}
}seg;
void init() {
	memset(lp,0x3f,sizeof(lp));
	memset(rp,0,sizeof(rp));
	bin[0]=1;for(rint i=1;i<=17;++i)bin[i]=bin[i-1]<<1;
	lg[0]=-1;for(rint i=1;i<=n;++i)lg[i]=lg[i>>1]+1;
}
void tarjan(int u) {
	dfn[u]=low[u]=++timer;
	sta[++top]=u;
	for(rint i=g.head[u];i;i=g.nxt[i]) {
		int v=g.to[i];
		if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
		else if(!scc[v])low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]) {
		scc[u]=++C,Lp[C]=lp[u],Rp[C]=rp[u];
		while(sta[top]!=u) {
			scc[sta[top]]=C;
			Lp[C]=min(Lp[C],lp[sta[top]]);
			Rp[C]=max(Rp[C],rp[sta[top]]);
			--top;
		}
		--top;
	}
} 
void build_DAG() {
	for(rint u=1;u<=maxpos;++u) {
		for(rint i=g.head[u];i;i=g.nxt[i]) {
			int v=g.to[i];
			if(scc[u]!=scc[v])dag.addedge(scc[v],scc[u]),++ind[scc[u]];
		}
	}
}
void toposort() {
	queue<int>q;
	for(rint i=1;i<=C;++i)if(!ind[i])q.push(i);
	while(!q.empty()) {
		int u=q.front();q.pop();
		for(rint i=dag.head[u];i;i=dag.nxt[i]) {
			int v=dag.to[i];
			Lp[v]=min(Lp[u],Lp[v]);
			Rp[v]=max(Rp[u],Rp[v]);
			--ind[v];
			if(!ind[v])q.push(v);
		}
	}
}
signed main() {
	n=rd(),init(),seg.build(1,n-1,1);
	for(rint i=1;i<=n;++i)a[i]=rd();
	for(rint i=1;i<=n;++i)
		st[0].st_min[0][a[i]]=i,
		st[0].st_max[0][a[i]]=i;
	st[0].n=n,st[0].init();
	for(rint i=1;i<n;++i) {
		lp[pos[i]]=st[0].query_min(a[i],a[i+1]);
		rp[pos[i]]=st[0].query_max(a[i],a[i+1]);
		seg.update(lp[pos[i]],rp[pos[i]]-1,1,n-1,1,pos[i]);
	}
	tarjan(1);
	build_DAG();
	toposort();
	for(rint i=1;i<n;++i)
		st[1].st_min[0][i]=Lp[scc[pos[i]]],
		st[1].st_max[0][i]=Rp[scc[pos[i]]];
	st[1].n=n-1,st[1].init();
	m=rd();
	while(m--) {
		int x=rd(),y=rd();
		if(x==y) {printf("%d %d\n",x,y);continue;}
		printf("%d %d\n",st[1].query_min(x,y-1),st[1].query_max(x,y-1));
	}
	return 0;
}
