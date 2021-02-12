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

const int K=103;
const int N=52*K;
const int D=K-2;
const int M=2*(K+52+52*K+2*52*52*K);
const int inf=0x3f3f3f3f;
int n,m,k,c,d,a[52],S,T;
int dis[N],mf,mc,inc[N],pre[N];
bool vis[N],inq[N];
struct edge{int nx,to,fl,c;}e[M];
int et=1,hed[N];
void addedge(int u,int v,int fl,int c){e[++et].nx=hed[u],e[et].to=v,e[et].fl=fl,e[et].c=c,hed[u]=et;}
void adde(int u,int v,int fl,int c){addedge(u,v,fl,c),addedge(v,u,0,-c);}
int id(int dep,int x){return (dep-1)*n+x;}
bool spfa(){
	queue<int>q;
	rep(i,1,T)dis[i]=inf,inq[i]=0;
	inc[S]=inf,dis[S]=0,q.push(S);
	while(!q.empty()){
		int u=q.front();q.pop(),inq[u]=0;
		for(int i=hed[u];i;i=e[i].nx){
			int v=e[i].to;
			if(e[i].fl&&ckmin(dis[v],dis[u]+e[i].c)){
                pre[v]=i,inc[v]=min(e[i].fl,inc[u]);
				if(!inq[v])inq[v]=1,q.push(v);
			}
		}
	}
	return dis[T]<inf;
}
void EK(){
    int rl=inc[T];
    mf+=rl;
    for(int u=T;u!=S;u=e[pre[u]^1].to)
        e[pre[u]].fl-=rl,e[pre[u]^1].fl+=rl,mc+=e[pre[u]].c*rl;
}
signed main(){
	n=read(),m=read(),k=read(),c=read(),d=read(),S=id(D,n)+1,T=S+1;
	rep(i,1,k)a[i]=read(),adde(S,id(1,a[i]),1,0);
	rep(i,1,m){
		int x=read(),y=read();
		rep(j,1,D-1)rep(l,0,k-1)adde(id(j,x),id(j+1,y),1,(2*l+1)*d+c),adde(id(j,y),id(j+1,x),1,(2*l+1)*d+c);
	}
	rep(i,1,D-1)rep(j,1,n)adde(id(i,j),id(i+1,j),k,c);
	rep(i,1,D)adde(id(i,1),T,k,0);
	while(spfa())EK();
	printf("%d\n",mc);
	return 0;
}
/*
3 3 4 2 3
3 2 2 3
1 2
2 3
2 3

*/