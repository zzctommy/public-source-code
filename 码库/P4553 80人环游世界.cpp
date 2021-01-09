#include<bits/stdc++.h>
using namespace std;
#define rint register int
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
typedef long long LL;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=250;
const int M=25000;
const int inf=1<<28;
int head[N],num_edge=1;
int n,m;
int s,t,S,T,SS,TT,S_;
int maxflow,sumflow,cost;
int dta[N],inq[N],dst[N],cur[N];
bool vis[N];
struct edge {
	int nxt,to,val,w;
}e[M];
void addedge(int from,int to,int val,int w) {
	++num_edge;
	e[num_edge].nxt=head[from];
	e[num_edge].to=to;
	e[num_edge].val=val;
	e[num_edge].w=w;
	head[from]=num_edge;
}
void addedge(int from,int to,int l,int r,int w) {
	addedge(from,to,r-l,w),addedge(to,from,0,-w);
	dta[from]-=l,dta[to]+=l;
}
bool spfa() {
	for(rint i=1;i<=TT;++i)cur[i]=head[i],inq[i]=0,dst[i]=inf;
	queue<int>q;q.push(s);dst[s]=0;
	while(!q.empty()) {
		int u=q.front();inq[u]=0,q.pop();
		for(rint i=head[u];i;i=e[i].nxt) {
			int v=e[i].to;
			if(e[i].val&&dst[v]>dst[u]+e[i].w) {
				dst[v]=dst[u]+e[i].w;
				if(!inq[v])inq[v]=1,q.push(v);
			}
		}
	}
	return dst[t]!=inf;
}
int dfs(int u,int flow) {
	vis[u]=1;
	if(u==t){maxflow+=flow;return flow;}
	int rlow,used=0;
	for(rint i=cur[u];i;i=e[i].nxt) {
		int v=e[i].to;cur[u]=i;
		if(dst[v]==dst[u]+e[i].w&&e[i].val&&(v==t||!vis[v])) {
			rlow=dfs(v,min(e[i].val,flow-used));
			if(rlow) {
				e[i].val-=rlow;
				e[i^1].val+=rlow;
				cost+=rlow*e[i].w;
				used+=rlow;
				if(used==flow)break;
			}
		}
	}
	return used;
}
void MCMF() {
	while(spfa()) {
		vis[t]=1;
		while(vis[t]){memset(vis,0,sizeof(vis)),dfs(s,inf);}
	}
}
signed main() {
	n=rd(),m=rd();
	S=n+n+1,S_=S+1,T=S_+1,SS=T+1,TT=SS+1;
	addedge(S_,S,m,m,0);
	for(rint i=1;i<=n;++i) {
		addedge(S,i,0,m,0);
		addedge(i+n,T,0,m,0);
		int x=rd();
		addedge(i,i+n,x,x,0);
	}
	for(rint i=1;i<=n;++i) {
		for(rint j=i+1;j<=n;++j) {
			int x=rd();
			if(~x)addedge(i+n,j,0,m,x);
		}
	}
	for(rint i=1;i<=T;++i)
		if(dta[i]>0)addedge(SS,i,0,dta[i],0);
		else addedge(i,TT,0,-dta[i],0);
	addedge(T,S_,0,inf,0);
	s=SS,t=TT,MCMF();
	printf("%d\n",cost);
	return 0;
}
