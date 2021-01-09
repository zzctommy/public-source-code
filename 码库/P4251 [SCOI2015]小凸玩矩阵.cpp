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

const int N=510;
const int M=(N*N+N*2)*2;
const int inf=0x3f3f3f3f;

int n,m,k,a[N][N],b[N*N],tot;
int dis[N],et=1,hed[N],S,T,mf,cur[N];
struct edge{int nx,to,fl;}e[M];
void addedge(int u,int v,int fl){e[++et].nx=hed[u],e[et].to=v,e[et].fl=fl,hed[u]=et;}
void adde(int u,int v,int fl){addedge(u,v,fl),addedge(v,u,0);}
bool bfs(int s,int t){
	queue<int>q;
	rep(i,1,T)dis[i]=0,cur[i]=hed[i];
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
	int used=0,rl;
	for(int i=cur[u];i;i=e[i].nx){
		int v=e[i].to;cur[u]=i;
		if(e[i].fl&&dis[v]==dis[u]+1){
			rl=dfs(v,min(fl-used,e[i].fl));
			if(rl){
				e[i].fl-=rl,e[i^1].fl+=rl,used+=rl;
				if(used==fl)break;
			}
		}
	}
	return used;
}
bool check(int o){
	memset(hed,0,sizeof(hed)),et=1,mf=0;
	rep(i,1,n)adde(S,i,1);
	rep(j,1,m)adde(j+n,T,1);
	rep(i,1,n)rep(j,1,m)if(a[i][j]<=o)adde(i,j+n,1);
	while(bfs(S,T))mf+=dfs(S,inf);
	return mf>=n-k+1;
}
signed main(){
	n=read(),m=read(),k=read(),S=n+m+1,T=S+1;
	rep(i,1,n)rep(j,1,m)a[i][j]=read(),b[++tot]=a[i][j];
	sort(b+1,b+tot+1);
	int l=1,r=tot,res=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(b[mid]))res=b[mid],r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",res);
	return 0;
}