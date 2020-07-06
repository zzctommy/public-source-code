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
const int N=110;
const int M=2.5e4+10;
const int inf=1e8;
struct edge {
	int to,nxt,val;
}e[M];
int num_edge=1,head[N];
int dep[N],cur[N],maxflow;
int n,s,t,ans;
int dta[N];
void addedge(int from,int to,int val) {
	++num_edge,e[num_edge].nxt=head[from],e[num_edge].to=to,e[num_edge].val=val,head[from]=num_edge;
	++num_edge,e[num_edge].nxt=head[to],e[num_edge].to=from,e[num_edge].val=0,head[to]=num_edge;
}
int bfs() {
	for(rint i=1;i<=n+4;++i)dep[i]=0,cur[i]=head[i];
	queue<int>q;dep[s]=1,q.push(s);
	while(!q.empty()) {
		int u=q.front();q.pop();
		for(rint i=head[u];i;i=e[i].nxt) {
			int v=e[i].to;
			if(!dep[v]&&e[i].val)q.push(v),dep[v]=dep[u]+1;
		}
	}
	return dep[t]>0;
}
int dfs(int u,int flow) {
	if(u==t) {
		maxflow+=flow;return flow;
	}
	int rlow,used=0;
	for(rint i=cur[u];i;i=e[i].nxt) {
		int v=e[i].to;cur[u]=i;
		if(e[i].val&&dep[v]==dep[u]+1) {
			rlow=dfs(v,min(flow-used,e[i].val));
			if(rlow)e[i].val-=rlow,e[i^1].val+=rlow,used+=rlow;
			if(used==flow)break;
		}
	}
	return used;
}
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i) {
		int m=rd();
		while(m--) {
			int x=rd();
			addedge(i,x,inf);
			--dta[i],++dta[x];
		}
	}
	int S=n+1,T=n+2,SS=n+3,TT=n+4;
	for(rint i=1;i<=n;++i) 
		if(dta[i]>0)addedge(SS,i,dta[i]);
		else addedge(i,TT,-dta[i]);
	for(rint i=1;i<=n;++i)
		addedge(S,i,inf),addedge(i,T,inf);
	s=SS,t=TT;
	while(bfs())dfs(s,inf);
	addedge(T,S,inf);
	while(bfs())dfs(s,inf);
	printf("%d\n",e[num_edge].val);
	return 0;
}
