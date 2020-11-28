//Orz cyn2006
#include<bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long LL;
#define pb(x) push_back(x)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 100005
#define M 200005
#define T (N<<1)
int n,m,tot,siz[T],val[T],S;
int stk[N],top,low[N],dfn[N],tmr;
LL ans;
struct edge{int nxt,to;}e[M<<1],E[T<<1];
int head[T],num_edge;
int Head[T],Num_edge;
void addedge(int fr,int to){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
void Addedge(int fr,int to){
	++Num_edge;
	E[Num_edge].nxt=Head[fr];
	E[Num_edge].to=to;
	Head[fr]=Num_edge;
}
void tarjan(int u){
	dfn[u]=low[u]=++tmr,++S,stk[++top]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tarjan(v),low[u]=min(low[u],low[v]);
			if(low[v]==dfn[u]){
				int num=1;++tot;
				Addedge(tot,u),Addedge(u,tot);
				while(stk[top+1]!=v){
					Addedge(tot,stk[top]),Addedge(stk[top],tot);
					--top,++num;
				}
				val[tot]=num;
			}
		}else low[u]=min(low[u],dfn[v]);
	}
}
void dfs(int u,int ft){
	siz[u]=u<=n;
	for(int i=Head[u];i;i=E[i].nxt){
		int v=E[i].to;if(v==ft)continue;
		dfs(v,u),ans+=2ll*siz[v]*siz[u]*val[u];
		siz[u]+=siz[v];
	}
	ans+=2ll*(S-siz[u])*siz[u]*val[u];
}
signed main(){
	tot=n=read(),m=read();
	for(int i=1;i<=m;++i){
		int x=read(),y=read();
		addedge(x,y),addedge(y,x);
	}
	for(int i=1;i<=n;++i)val[i]=-1;
	for(int i=1;i<=n;++i)if(!dfn[i])S=top=0,tarjan(i),dfs(i,0);
	printf("%lld\n",ans);
	return 0;
}
/*
4 3
1 2
2 3
3 4

*/