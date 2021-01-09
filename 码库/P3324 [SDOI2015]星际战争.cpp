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
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}

const int K=55;
const int N=K*5;
const int M=(N*4+N*N)*2;
const db inf=1e15;
const db eps=1e-7;

int n,m,a[N],b[N],c[N][N];
int dis[N],cur[N],S,T,hed[N],et=1,control=0;
db mf;
struct edge{int nx,to;db fl;}e[M];
void addedge(int u,int v,db fl){e[++et].to=v,e[et].nx=hed[u],e[et].fl=fl,hed[u]=et;}
void adde(int u,int v,db fl){
	if(control){
		if(fabs(fl-inf)<eps)cerr<<u<<' '<<v<<' '<<"inf\n";
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
			if(e[i].fl>eps&&!dis[v]){
				dis[v]=dis[u]+1,q.push(v);
				if(v==t)return 1;
			}
		}
	}
	return 0;
}
db dfs(int u,db fl){
	if(u==T)return fl;
	db rl,used=0;
	for(int i=cur[u];i;i=e[i].nx){
		int v=e[i].to;cur[u]=i;
		if(e[i].fl&&dis[v]==dis[u]+1){
			rl=dfs(v,min(e[i].fl,fl-used));
			if(rl>eps){
				e[i].fl-=rl,e[i^1].fl+=rl,used+=rl;
				if(used+eps>fl)break;
			}
		}
	}
	return used;
}
bool check(db o){
	et=1,mf=0,memset(hed,0,sizeof(hed));
	rep(i,1,m)adde(S,i,1.*o*b[i]);
	rep(i,1,n)adde(i+m,T,a[i]);
	rep(i,1,m)rep(j,1,n)if(c[i][j])adde(i,j+m,inf);
	while(bfs(S,T))mf+=dfs(S,inf);
	return mf+eps>a[0];
}
signed main(){
	n=read(),m=read(),S=m+n+1,T=S+1;;
	rep(i,1,n)a[i]=read(),a[0]+=a[i];
	rep(i,1,m)b[i]=read();
	rep(i,1,m)rep(j,1,n)c[i][j]=read();
	db l=0,r=1e7;
	while(r-l>eps){
		db mid=(l+r)/2;
		if(check(mid))r=mid;
		else l=mid;
	}
	printf("%.6lf\n",l);
	return 0;
}
/*
2 2
3 10
4 6
0 1
1 1

*/