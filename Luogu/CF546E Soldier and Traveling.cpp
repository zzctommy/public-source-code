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

const int N=305;
const int M=2005;
const int inf=0x3f3f3f3f;

int n,m,a[N],b[N],ans[N][N];
int dis[N],cur[N],mf,S,T,hed[N],et=1;
struct edge{int nx,to,fl;}e[M];
void addedge(int u,int v,int fl){e[++et].to=v,e[et].nx=hed[u],e[et].fl=fl,hed[u]=et;}
void adde(int u,int v,int fl){addedge(u,v,fl),addedge(v,u,0);}
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
			if(fl){
				e[i].fl-=rl,e[i^1].fl+=rl,used+=rl;
				if(used==fl)break;
			}
		}
	}
	return used;
}

signed main(){
	n=read(),m=read(),S=n*3+1,T=S+1;
	rep(i,1,n)a[i]=read(),adde(S,i,a[i]),adde(i,i+n,a[i]),adde(i+n,i+2*n,inf),a[0]+=a[i];
	rep(i,1,n)b[i]=read(),adde(i+n*2,T,b[i]),b[0]+=b[i];
	if(a[0]!=b[0])return puts("NO"),0;
	rep(i,1,m){
		int x=read(),y=read();
		adde(x+n,y+2*n,inf),adde(y+n,x+2*n,inf);
	}
	while(bfs(S,T))mf+=dfs(S,inf);
	if(mf!=b[0])return puts("NO"),0;
	puts("YES");
	for(int i=2;i<=et;++i){
		if(e[i].to>2*n&&e[i].to<=3*n&&e[i^1].to>n&&e[i^1].to<=2*n){
			ans[e[i^1].to-n][e[i].to-2*n]=e[i^1].fl;
		}
	}
	rep(i,1,n)rep(j,1,n)printf("%d%c",ans[i][j]," \n"[j==n]);
	return 0;
}
/*
4 4
1 2 6 3
3 5 3 1
1 2
2 3
3 4
4 2

*/