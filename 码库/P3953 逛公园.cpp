#include<bits/stdc++.h>
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define N 100005
#define M 200005
#define K 55
int n,m,k,mod,ans,flg,dis[N],dp[N][K];
bool vis[N],ins[N][K];
void fmod(int&x){x-=mod,x+=x>>31&mod;}
struct edge{
	int nxt,to,val;
}e[M],E[M];
int head[N],num_edge,Head[N],Num_edge;
void addedge(int fr,int to,int val){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].val=val;
	e[num_edge].to=to;
	head[fr]=num_edge;
}
void Addedge(int fr,int to,int val){
	++Num_edge;
	E[Num_edge].nxt=Head[fr];
	E[Num_edge].val=val;
	E[Num_edge].to=to;
	Head[fr]=Num_edge;
}
void clear(){
	ans=0;
	memset(dp,-1,sizeof(dp));
	memset(head,0,sizeof(head));
	memset(Head,0,sizeof(Head));
	num_edge=Num_edge=0,flg=1;
}
struct Dij{
	int u,dis;
	Dij(int u_,int d_){u=u_,dis=d_;}
	inline bool operator < (const Dij&t)const{return dis>t.dis;}
};
priority_queue<Dij>q;
void dij(){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	q.push(Dij(1,dis[1]=0));
	while(!q.empty()){
		Dij now=q.top();q.pop();
		int u=now.u;
		if(vis[u])continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].val){
				dis[v]=dis[u]+e[i].val;
				if(!vis[v])q.push(Dij(v,dis[v]));
			}
		}
	}
}
int dfs(int u,int lft){
	if(!flg)return 0;
	if(ins[u][lft])return flg=0;
	if(~dp[u][lft])return dp[u][lft];
	int res=0;
	ins[u][lft]=1;
	for(int i=Head[u];i&&flg;i=E[i].nxt){
		int v=E[i].to;
		int w=lft-(E[i].val-(dis[u]-dis[v]));
		if(w>=0)fmod(res+=dfs(v,w));
	}
	ins[u][lft]=0;
	if(u==1&&!lft)++res;
	return dp[u][lft]=res;
}
void Main(){
	clear();
	n=read(),m=read(),k=read(),mod=read();
	for(int i=1;i<=m;++i){
		int x=read(),y=read(),z=read();
		addedge(x,y,z),Addedge(y,x,z);
	}
	dij();
	for(int i=0;flg&&i<=k;++i)fmod(ans+=dfs(n,i));
	flg?printf("%d\n",ans):puts("-1");
}
signed main(){for(int T=read();T;--T)Main();}