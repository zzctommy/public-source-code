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

const int K=205;
const int N=K*K;
const int M=N*7*2;
const int inf=0x3f3f3f3f;

int n,m,a[K][K],ans;
int dis[N],cur[N],mf,S,T,hed[N],et=1,control=0;
struct edge{int nx,to,fl;}e[M];
void addedge(int u,int v,int fl){e[++et].to=v,e[et].nx=hed[u],e[et].fl=fl,hed[u]=et;}
void adde(int u,int v,int fl){
	if(control){
		if(fl==inf)cerr<<u<<' '<<v<<' '<<"inf\n";
		else cerr<<u<<' '<<v<<' '<<fl<<'\n';
	}
	addedge(u,v,fl),addedge(v,u,0);
}
bool bfs(int s,int t){
	queue<int>q;
	rep(i,1,T)cur[i]=hed[i],dis[i]=0;
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
	return used;
}
int id(int x,int y){return (x-1)*m+y;}
signed main(){
	n=read(),m=read(),S=n*m+1,T=S+1;
	rep(i,1,n)rep(j,1,m){
		int x=read();
		if(x>0)adde(S,id(i,j),x),ans+=x;
		else if(x<0)adde(id(i,j),T,-x),ans-=x;
	}
	rep(i,1,n-1)rep(j,1,m){
		int x=read();
		adde(id(i,j),id(i+1,j),x);
		adde(id(i+1,j),id(i,j),x);
	}
	rep(i,1,n)rep(j,1,m-1){
		int x=read();
		adde(id(i,j),id(i,j+1),x);
		adde(id(i,j+1),id(i,j),x);
	}
	while(bfs(S,T))mf+=dfs(S,inf);
	printf("%d\n",ans-=mf);
	return 0;
}