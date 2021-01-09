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

const int N=410;
const int M=N*N*2;
const LL inf=4e18;

int n,m;
LL s[N],p[N],mp[N][N],mf,sum;
int dis[N],et=1,hed[N],S,T,cur[N];
struct edge{int nx,to;LL fl;}e[M];
void addedge(int u,int v,LL fl){e[++et].nx=hed[u],e[et].to=v,e[et].fl=fl,hed[u]=et;}
void adde(int u,int v,LL fl){addedge(u,v,fl),addedge(v,u,0);}
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
LL dfs(int u,LL fl){
	if(u==T)return fl;
	LL used=0,rl;
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
bool check(LL o){
	memset(hed,0,sizeof(hed)),et=1,mf=0;
	rep(i,1,n)adde(S,i,s[i]),adde(i+n,T,p[i]);
	rep(i,1,n)rep(j,1,n)if(mp[i][j]<=o)adde(i,j+n,inf);
	while(bfs(S,T))mf+=dfs(S,inf);
	return mf==sum;
}
signed main(){
	scanf("%d%d",&n,&m),S=n*2+1,T=S+1;
	rep(i,1,n)scanf("%lld%lld",&s[i],&p[i]),sum+=s[i];
	memset(mp,0x3f,sizeof(mp));
	rep(i,1,n)mp[i][i]=0;
	rep(i,1,m){
		int x,y;LL z;scanf("%d%d%lld",&x,&y,&z);
		ckmin(mp[x][y],z),ckmin(mp[y][x],z);
	}
	rep(k,1,n)rep(i,1,n)rep(j,1,n)ckmin(mp[i][j],mp[i][k]+mp[k][j]);
	LL l=1,r=1e18,res=-1;
	check(842);
	while(l<=r){
		LL mid=(l+r)>>1;
		if(check(mid))r=mid-1,res=mid;
		else l=mid+1;
	}
	printf("%lld\n",res);
	return 0;
}