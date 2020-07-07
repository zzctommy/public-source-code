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
const int N=410;
const int M=1010;
const int K=1500;
const int inf=1e8;
const int L=2*(N*N+M+K);
int n,m,G[M],C[N],D[N],ans;
int num_edge,head[K];
int s,t,S,T,SS,TT,dta[K];
int cur[K],dep[K],maxflow,sumflow;
struct edge {
	int nxt,to,val;
}e[L];
void addedge(int from,int to,int val) {
	++num_edge;e[num_edge].nxt=head[from];e[num_edge].to=to;e[num_edge].val=val;head[from]=num_edge;
	++num_edge;e[num_edge].nxt=head[to];e[num_edge].to=from;e[num_edge].val=0;head[to]=num_edge;
}
void clear() {
	memset(head,0,sizeof(head));
	memset(dta,0,sizeof(dta));
	num_edge=1;ans=0;sumflow=0;maxflow=0;
}
bool bfs() {
	for(rint i=1;i<=TT;++i)cur[i]=head[i],dep[i]=0;
	dep[s]=1;queue<int>q;q.push(s);
	while(!q.empty()) {
		int u=q.front();q.pop();
		for(rint i=head[u];i;i=e[i].nxt) {
			int v=e[i].to;
			if(e[i].val&&!dep[v])dep[v]=dep[u]+1,q.push(v);
		}
	}
	return dep[t]>0;
}
int dfs(int u,int flow) {
	if(u==t)return flow;
	int rlow,used=0;
	for(rint i=cur[u];i;i=e[i].nxt) {
		cur[u]=i;int v=e[i].to;
		if(e[i].val&&dep[v]==dep[u]+1) {
			rlow=dfs(v,min(e[i].val,flow-used));
			if(rlow) {
				e[i].val-=rlow;
				e[i^1].val+=rlow;
				used+=rlow;
				if(used==flow)break;
			}
		}
	}
	return used;
}
void Main() {
	clear();
	S=n+m+1,T=S+1,SS=T+1,TT=SS+1;
	for(rint i=1;i<=m;++i)
		G[i]=rd(),addedge(i+n,T,inf-G[i]),dta[i+n]-=G[i],dta[T]+=G[i];
	for(rint i=1;i<=n;++i) {
		C[i]=rd(),D[i]=rd();
		addedge(S,i,D[i]);
		for(rint j=1;j<=C[i];++j) {
			int t=rd()+1,l=rd(),r=rd();
			addedge(i,t+n,r-l);
			dta[t+n]+=l,dta[i]-=l;
		}
	}
	for(rint i=1;i<=n+m+2;++i)
		if(dta[i]>0)addedge(SS,i,dta[i]),sumflow+=dta[i];
		else addedge(i,TT,-dta[i]);
	addedge(T,S,inf);
	s=SS,t=TT;while(bfs())maxflow+=dfs(s,inf);
	if(sumflow!=maxflow){printf("%d\n\n",-1);return;}
	s=S,t=T;while(bfs())ans+=dfs(s,inf);
	printf("%d\n\n",ans);
}
signed main() {
	while(scanf("%d%d",&n,&m)!=EOF)Main();
	return 0;
}
