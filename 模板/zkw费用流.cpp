#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
const int N=5005;
const int M=100005;
int n,m,s,t;
int num_edge=1,head[N];
int maxflow,cost;
bool vis[N],inq[N];
int dist[N],cur[N];
struct edge {
	int to,val,w,nxt;
} e[M];
void add(int from,int to,int val,int w) {
	++num_edge;
	e[num_edge].to=to;
	e[num_edge].val=val;
	e[num_edge].w=w;
	e[num_edge].nxt=head[from];
	head[from]=num_edge;
}
bool spfa(int st) {
	queue<int>q;
	q.push(st);
	for(int i=1;i<=n;++i)
		dist[i]=0x3f3f3f3f,inq[i]=0,cur[i]=head[i];
	dist[st]=0;
	inq[st]=true;
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		inq[u]=false;
		for(int i=head[u]; i; i=e[i].nxt) {
			int v=e[i].to;
			if(dist[v]>dist[u]+e[i].w&&e[i].val) {
				dist[v]=dist[u]+e[i].w;
				if(!inq[v]) {
					inq[v]=true;
					q.push(v);
				}
			}
		}
	}
	return dist[t]!=0x3f3f3f3f;
}
int dfs(int u,int flow) {
	if(u==t) {
		maxflow+=flow;
		vis[t]=true;
		return flow;
	}
	int used=0,rlow;
	vis[u]=1;
	for(int i=cur[u]; i; i=e[i].nxt) {
		int v=e[i].to;cur[u]=i;
		if(dist[v]==dist[u]+e[i].w&&e[i].val&&(v==t||!vis[v])) {
			rlow=dfs(v,min(e[i].val,flow-used));
			if(rlow) {
				e[i].val-=rlow;
				e[i^1].val+=rlow;
				cost+=rlow*e[i].w;
				used+=rlow;
			}
			if(used==flow)break;
		}
	}
	return used;
}
void mincostmaxflow() {
	while(spfa(s)) {
		vis[t]=true;
		while(vis[t]) {
			memset(vis,false,sizeof(vis));
			dfs(s,inf);
		}
	}
}
int main() {
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1; i<=m; i++) {
		int u,v,val,w;
		scanf("%d%d%d%d",&u,&v,&val,&w);
		add(u,v,val,w);
		add(v,u,0,-w);
	}
	mincostmaxflow();
	printf("%d %d\n",maxflow,cost);
	return 0;
}