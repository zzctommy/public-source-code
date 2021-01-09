#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}

const int N=4005;
const int M=60005*2;
const int inf=0x3f3f3f3f;

int n,m,U[M],V[M];
int dfn[N],tmr,low[N],scc[N],C,stk[N],top;
int dis[N],cur[N],mf,S,T,hed[N],et=1,control=0;
struct edge{int nx,to,fl;}e[M];
void addedge(int u,int v,int fl){assert(et<M-1),e[++et].to=v,e[et].nx=hed[u],e[et].fl=fl,hed[u]=et;}
void adde(int u,int v,int fl){
	if(control){
		if(fl==inf)cout<<u<<' '<<v<<' '<<"inf\n";
		else cout<<u<<' '<<v<<' '<<fl<<'\n';
	}
	addedge(u,v,fl),addedge(v,u,0);
}
bool bfs(int s,int t){
	queue<int>q;
	rep(i,1,n)cur[i]=hed[i],dis[i]=0;
	q.push(s),dis[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=hed[u];i;i=e[i].nx){
			int v=e[i].to;
			if(e[i].fl&&!dis[v]){
				dis[v]=dis[u]+1,q.push(v);
				if(v==t)return 1;
			}
		}
	}
	return 0;
}
int dfs(int u,int fl){
	if(u==T)return fl;
	int rl,used=0;
	for(int i=cur[u];i;i=e[i].nx){
		int v=e[i].to;cur[u]=i;
		if(e[i].fl&&dis[v]==dis[u]+1){
			rl=dfs(v,min(e[i].fl,fl-used));
			if(rl){
				e[i].fl-=rl,e[i^1].fl+=rl,used+=rl;
				if(used==fl)break;
			}
		}
	}
	if(!used)dis[u]=0;
	return used;
}
void tarjan(int u){
	dfn[u]=low[u]=++tmr,stk[++top]=u;
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(!e[i].fl)continue;
		if(!dfn[v])tarjan(v),ckmin(low[u],low[v]);
		else if(!scc[v])ckmin(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		scc[u]=++C;
		while(stk[top]!=u)scc[stk[top--]]=C;
		--top;
	}
}
signed main(){
	n=read(),m=read(),S=read(),T=read();
	rep(i,1,m)U[i]=read(),V[i]=read(),adde(U[i],V[i],read());
	while(bfs(S,T))dfs(S,inf);
	rep(i,1,n)if(!dfn[i])tarjan(i);
	rep(i,1,m)
		if(!e[i<<1].fl)printf("%d %d\n",scc[U[i]]!=scc[V[i]],scc[U[i]]==scc[S]&&scc[V[i]]==scc[T]);
		else puts("0 0");
	return 0;
}
/*
6 7 1 6
1 2 3
1 3 2
2 4 4
2 5 1
3 5 5
4 6 2
5 6 3

*/