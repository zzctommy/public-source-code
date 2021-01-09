#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=2005;
const int inf=1e8;
const LL linf=1e16;
int n,W,a[N],S,T;
int cost,cur[N];
LL dis[N];
bool vis[N],inq[N];
struct edge{
    int nxt,to,val,w;
}e[(N*N+N*3)<<1];
int head[N],num_edge=1;
void addedge(int fr,int to,int val,int w){
    ++num_edge;
    e[num_edge].nxt=head[fr];
    e[num_edge].to=to;
    e[num_edge].val=val;
    e[num_edge].w=w;
    head[fr]=num_edge;
}
void adde(int fr,int to,int val,int w){
    addedge(fr,to,val,w),addedge(to,fr,0,-w);
}
bool spfa(){
    queue<int>q;
    rep(i,1,T)dis[i]=linf,cur[i]=head[i],inq[i]=0;
    q.push(S),dis[S]=0;
    while(!q.empty()){
        int u=q.front();q.pop();inq[u]=0;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(e[i].val&&dis[v]>dis[u]+e[i].w){
                dis[v]=dis[u]+e[i].w;
				if(!inq[v])inq[v]=1,q.push(v);
            }
        }
    }
	return dis[T]!=linf;
}
int dfs(int u,int flow){
	vis[u]=1;
	if(u==T)return flow;
	int used=0,rlow;
	for(int i=cur[u];i;i=e[i].nxt){
		cur[u]=i;int v=e[i].to;
		if(e[i].val&&dis[v]==dis[u]+e[i].w&&(v==T||!vis[v])){
			rlow=dfs(v,min(e[i].val,flow-used));
			if(rlow)e[i].val-=rlow,e[i^1].val+=rlow,cost+=rlow*e[i].w,used+=rlow;
			if(used==flow)break;
		}
	}
	return used;
}
void MCMF(){
    while(spfa()){
        vis[T]=1;
        while(vis[T])fill(vis,vis+T+1,0),dfs(S,inf);
    }
}
signed main(){
    n=read(),W=read(),S=n<<1|1,T=S+1;
    rep(i,1,n)a[i]=read();
    rep(i,1,n)adde(S,i,1,0),adde(i+n,T,1,0),adde(S,i+n,1,W);
    rep(i,1,n)rep(j,i+1,n)if(abs(a[i]-a[j])<W)adde(i,j+n,1,abs(a[i]-a[j]));
    MCMF();
    printf("%d\n",cost);
    return 0;
}