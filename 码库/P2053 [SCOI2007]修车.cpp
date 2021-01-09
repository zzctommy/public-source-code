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
const int N=620;
const int M=66010;
const int inf=1<<28;
int head[N],num_edge=1;
int n,m,s,t;
int T[65][11];
int dst[N],cur[N],inq[N],maxflow,cost,vis[N];
struct edge {
	int val,w,to,nxt;
}e[M];
void addedge_(int from,int to,int val,int w) {
	++num_edge;
	e[num_edge].nxt=head[from];
	e[num_edge].to=to;
	e[num_edge].val=val;
	e[num_edge].w=w;
	head[from]=num_edge;
}
void addedge(int from,int to,int val,int w) {
	addedge_(from,to,val,w),addedge_(to,from,0,-w);
}
bool spfa() {
	for(rint i=1;i<=t;++i)dst[i]=inf,cur[i]=head[i],inq[i]=0;
	queue<int>q;q.push(s),dst[s]=0;
	while(!q.empty()) {
		int u=q.front();q.pop(),inq[u]=0;
		for(rint i=head[u];i;i=e[i].nxt) {
			int v=e[i].to;
			if(dst[v]>dst[u]+e[i].w&&e[i].val) {
				dst[v]=dst[u]+e[i].w;
				if(!inq[v])q.push(v),inq[v]=1;
			}
		}
	}
	return dst[t]!=inf;
}
int dfs(int u,int flow) {
	vis[u]=1;
	if(u==t)return flow;
	int rlow,used=0;
	for(rint i=cur[u];i;i=e[i].nxt) {
		int v=e[i].to;cur[u]=i;
		if(e[i].val&&dst[v]==dst[u]+e[i].w&&(v==t||!vis[v])) {
			rlow=dfs(v,min(e[i].val,flow-used));
			if(rlow) {
				e[i].val-=rlow;
				e[i^1].val+=rlow;
				used+=rlow;
				cost+=rlow*e[i].w;
				if(used==flow)break;
			}
		}
	}
	return used;
}
void MCMF() {
	maxflow=cost=0;
	while(spfa()) {
		vis[t]=1;
		while(vis[t])memset(vis,0,sizeof(vis)),maxflow+=dfs(s,inf);
	}
}
signed main() {
	m=rd(),n=rd(),s=n*m+n+1,t=s+1;
	for(rint i=1;i<=n;++i) 
		for(rint j=1;j<=m;++j)
			T[i][j]=rd();
	for(rint i=1;i<=n;++i)addedge(s,i,1,0);
	for(rint i=1;i<=m;++i)
		for(rint j=1;j<=n;++j)
			addedge((i-1)*n+j+n,t,1,0);
	for(rint i=1;i<=n;++i) {
		for(rint j=1;j<=m;++j) {
			for(rint k=1;k<=n;++k) {
				addedge(i,(j-1)*n+k+n,1,T[i][j]*k);
			}
		}
	}
	MCMF();
	printf("%.2lf\n",1.0*cost/n);
	return 0;
}
