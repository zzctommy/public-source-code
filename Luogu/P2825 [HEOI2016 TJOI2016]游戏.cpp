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
#define broken cerr<<"lqx AK:"<<__LINE__<<' '<<__FUNCTION__<<endl
#define outedge cerr<<u<<' '<<v<<' '<<fl<<'\n'
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}

const int K=55;
const int N=5005;
const int M=N*4*2;
const int inf=0x3f3f3f3f;

int n,m,a[K][K],idx[K][K],idy[K][K],tot;
int dis[N],cur[N],mf,S,T,hed[N],et=1;
struct edge{int nx,to,fl;}e[M];
void addedge(int u,int v,int fl){e[++et].to=v,e[et].nx=hed[u],e[et].fl=fl,hed[u]=et;}
void adde(int u,int v,int fl){addedge(u,v,fl),addedge(v,u,0);}
bool bfs(int s,int t){
	queue<int>q;
	rep(i,1,tot)cur[i]=hed[i],dis[i]=0;
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
signed main(){
	n=read(),m=read(),S=++tot,T=++tot;
	memset(a,-1,sizeof(a));
	rep(i,1,n)rep(j,1,m){
		char ch=getchar();
		while(ch!='x'&&ch!='*'&&ch!='#')ch=getchar();
		if(ch=='#')a[i][j]=-1;
		else if(ch=='x')a[i][j]=0;
		else a[i][j]=1;
	}
	rep(i,1,n)rep(j,1,m){
		if(!~a[i][j])continue;
		if(!~a[i][j-1])idx[i][j]=++tot,adde(S,tot,1);
		else idx[i][j]=idx[i][j-1];
	}
	rep(j,1,m)rep(i,1,n){
		if(!~a[i][j])continue;
		if(!~a[i-1][j])idy[i][j]=++tot,adde(tot,T,1);
		else idy[i][j]=idy[i-1][j];
	}
	rep(i,1,n)rep(j,1,m)if(a[i][j]==1)adde(idx[i][j],idy[i][j],1);
	while(bfs(S,T))mf+=dfs(S,inf);
	printf("%d\n",mf);
	return 0;
}