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

const int N=1205;
const int M=(N*N+N*2)*2;
const int inf=0x3f3f3f3f;

int n,m,c,lim,a[N],mp[N][N];
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
	rep(i,1,n)if(a[i])adde(S,i,a[i]);
	rep(i,1,n)adde(i+n,T,1);
	rep(i,1,n)rep(j,1,n)if(mp[i][j]<=o)adde(i,j+n,inf);
	while(bfs(S,T))mf+=dfs(S,inf);
	return mf>=lim;
}
signed main(){
	n=read(),m=read(),c=read(),lim=read(),S=n+n+1,T=S+1;
	rep(i,1,c)++a[read()];
	memset(mp,0x3f,sizeof(mp));
	rep(i,1,n)mp[i][i]=0;
	rep(i,1,m){
		int x=read(),y=read(),z=read();
		ckmin(mp[x][y],z),ckmin(mp[y][x],z);
	}
	rep(k,1,n)rep(i,1,n)rep(j,1,n)ckmin(mp[i][j],mp[i][k]+mp[k][j]);
	int l=0,r=1731311,res=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))r=mid-1,res=mid;
		else l=mid+1;
	}
	printf("%d\n",res);
	return 0;
}
/*
6 7 5 4
5 5 2 2 5
1 3 3
1 5 2
1 6 5
2 5 4
2 6 7
3 4 11
3 5 3

*/