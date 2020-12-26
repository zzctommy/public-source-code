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

const int K=45;
const int N=K*K+5;
const int M=(N*N*4+2*N*N)*2;
const LL inf=1e14;

int n,m,a[K][K],c[2],mxv;
LL sum[2];
int dis[N],cur[N],S,T,hed[N],et=1,control=0;
LL mf;
struct edge{int nx,to;LL fl;}e[M];
void addedge(int u,int v,LL fl){e[++et].to=v,e[et].nx=hed[u],e[et].fl=fl,hed[u]=et;}
void adde(int u,int v,LL fl){
	if(control)cerr<<u<<' '<<v<<' '<<fl<<'\n';
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
LL dfs(int u,LL fl){
	if(u==T)return fl;
	LL rl,used=0;
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
bool check(LL o){
	et=1,mf=0,memset(hed,0,sizeof(hed));
	rep(i,1,n)rep(j,1,m){
		if((i+j)&1){
			adde(S,id(i,j),o-a[i][j]);
			if(i>1)adde(id(i,j),id(i-1,j),inf);
			if(i<n)adde(id(i,j),id(i+1,j),inf);
			if(j>1)adde(id(i,j),id(i,j-1),inf);
			if(j<m)adde(id(i,j),id(i,j+1),inf);
		}else adde(id(i,j),T,o-a[i][j]);
	}
	while(bfs(S,T))mf+=dfs(S,inf);
	return mf==1ll*c[0]*o-sum[0];
}
void Main(){
	n=read(),m=read(),S=n*m+1,T=S+1,c[0]=c[1]=mxv=sum[0]=sum[1]=0;
	rep(i,1,n)rep(j,1,m)a[i][j]=read(),++c[(i+j)&1],sum[(i+j)&1]+=a[i][j],ckmax(mxv,a[i][j]);
	if(c[0]!=c[1]){
		LL res=(sum[0]-sum[1])/(c[0]-c[1]);
		if(check(res))printf("%lld\n",mf);
		else puts("-1");
	}else{
		LL l=mxv,r=inf,res=-1;
		while(l<=r){
			LL mid=(l+r)>>1;
			if(check(mid))res=mf,r=mid-1;
			else l=mid+1;
		}
		printf("%lld\n",res);
	}
}
signed main(){for(int T=read();T;--T)Main();}
/*
2 
2 2 
1 2 
2 3 
3 3 
1 2 3 
2 3 4 
4 3 2 

*/