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
#define per(i,y,x) for(int i=y,i##end=x;i>=i##end;--i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}

const int N=55;
const int M=N*N*2;
const int inf=0x3f3f3f3f;
int n,a1,a2,an,b1,b2,bn;
int hed[N],et=1,S,T,maxflow,cur[N],dis[N];
struct edge{int nx,to,fl;}e[M];
void addedge(int u,int v,int fl){e[++et].nx=hed[u],e[et].to=v,e[et].fl=fl,hed[u]=et;}
void adde(int u,int v,int fl){addedge(u,v,fl),addedge(v,u,0);}
bool bfs(int s,int t){
	queue<int>q;
	rep(i,1,T)dis[i]=0,cur[i]=hed[i];
	dis[s]=1,q.push(s);
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
	int rl=0,used=0;
	for(int i=cur[u];i;i=e[i].nx){
		int v=e[i].to;cur[u]=i;
		if(e[i].fl&&dis[v]==dis[u]+1){
			rl=dfs(v,min(e[i].fl,fl-used));
			if(rl)e[i].fl-=rl,e[i^1].fl+=rl,used+=rl;
		}
	}
	return used;
}
void Main(){
	fill(hed,hed+n+3,0),et=1,S=n+1,T=S+1;
	a1=read()+1,a2=read()+1,an=read(),b1=read()+1,b2=read()+1,bn=read();
	rep(i,1,n){
		rep(j,1,n){
			char ch=getchar();
			while(ch!='O'&&ch!='N'&&ch!='X')ch=getchar();
			if(ch=='X')continue;
			if(ch=='O')adde(i,j,1);
			else adde(i,j,inf);
		}
	}
	hed[S]=hed[T]=maxflow=0;
	adde(S,a1,an),adde(a2,T,an),adde(S,b1,bn),adde(b2,T,bn);
	while(bfs(S,T))maxflow+=dfs(S,inf);
	if(maxflow!=an+bn)return puts("No"),void();

	hed[S]=hed[T]=maxflow=0;
	rep(i,1,et)if(!(i&1))e[i^1].fl+=e[i].fl,e[i].fl=0;
	adde(S,a1,an),adde(a2,T,an),adde(S,b2,bn),adde(b1,T,bn);
	while(bfs(S,T))maxflow+=dfs(S,inf);
	if(maxflow!=an+bn)return puts("No"),void();
	puts("Yes");
}
signed main(){while(scanf("%d",&n)!=EOF)Main();}