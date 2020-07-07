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
const int N=5010;
const int M=100010;
const int inf=1<<28;
int head[N],num_edge=1;
int n,m,s,t;
int maxflow,cost;
int inq[N],dst[N],cur[N];
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
bool spfa() {
	for(rint i=1;i<=n;++i)cur[i]=head[i],inq[i]=0,dst[i]=inf;
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
	maxflow=cost=0;
	while(spfa()) {
		vis[t]=1;
		while(vis[t]){memset(vis,0,sizeof(vis)),dfs(s,inf);}
	}
}
signed main() {
	n=rd(),m=rd(),s=rd(),t=rd();
	for(rint i=1;i<=m;++i) {
		int x=rd(),y=rd(),z=rd(),w=rd();
		addedge(x,y,z,w),addedge(y,x,0,-w);
	}
	MCMF();
	cout<<maxflow<<' '<<cost<<endl;
	return 0;
}
