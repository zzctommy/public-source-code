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
const int N=210;
const int inf=1<<29;
const int M=2*(N+N+N*N+N);
struct edge {
    int to,nxt,val;
}e[M];
int num_edge=1,head[N];
int dep[N],cur[N],dta[N],maxflow,ans,sumflow;
int n,m,k,a[N>>1][N>>1];
int s,t,S,T,SS,TT;
void addedge(int from,int to,int val) {
    ++num_edge,e[num_edge].nxt=head[from],e[num_edge].to=to,e[num_edge].val=val,head[from]=num_edge;
    ++num_edge,e[num_edge].nxt=head[to],e[num_edge].to=from,e[num_edge].val=0,head[to]=num_edge;
}
void addedge(int from,int to,int l,int r) {
	addedge(from,to,r-l),addedge(to,from,0);
	dta[from]-=l,dta[to]+=l;
}
int bfs() {
    for(rint i=1;i<=TT;++i)dep[i]=0,cur[i]=head[i];
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
    if(u==t) {maxflow+=flow;return flow;}
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
	m=rd(),n=rd(),k=rd();S=n+m+1,T=S+1,SS=T+1,TT=SS+1;
	for(rint i=1;i<=m;++i)addedge(S,i,rd(),inf);
	for(rint i=1;i<=n;++i)addedge(i+m,T,rd(),inf);
	for(rint i=1;i<=k;++i) {
		int x=rd(),y=rd();
		a[x][y]=1;
	}
	for(rint i=1;i<=m;++i)
		for(rint j=1;j<=n;++j)
			if(!a[i][j])addedge(i,j+m,0,1);
	for(rint i=1;i<=T;++i)
		if(dta[i]>0)addedge(SS,i,0,dta[i]),sumflow+=dta[i];
		else addedge(i,TT,0,-dta[i]);
	s=SS,t=TT;
	while(bfs())dfs(s,inf);
	addedge(T,S,0,inf);
	while(bfs())ans+=dfs(s,inf);
	if(maxflow!=sumflow)return puts("JIONG!"),0;
	printf("%d\n",ans);
	return 0;
}
