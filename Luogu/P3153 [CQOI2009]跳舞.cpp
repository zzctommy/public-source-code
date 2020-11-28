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
const int inf=0x3f3f3f3f;

int n,k,a[K][K];
int dis[N],cur[N],mf,S,T,hed[N],et=1,control=0;
struct edge{int nx,to,fl;}e[M];
void addedge(int u,int v,int fl){e[++et].to=v,e[et].nx=hed[u],e[et].fl=fl,hed[u]=et;}
void adde(int u,int v,int fl){
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
bool check(int o){
	memset(hed,0,sizeof(hed)),et=1,mf=0,S=n*4+1,T=S+1;
	rep(i,1,n)adde(S,i,o),adde(i+3*n,T,o),adde(i,i+n,k),adde(i+2*n,i+3*n,k);
	rep(i,1,n)rep(j,1,n)
		if(a[i][j])adde(i,j+3*n,1);
		else adde(i+n,j+2*n,1);
	while(bfs(S,T))mf+=dfs(S,inf);
	return mf==n*o;
}
signed main(){
	n=read(),k=read();
	rep(i,1,n)rep(j,1,n){
		char ch=getchar();
		while(ch!='Y'&&ch!='N')ch=getchar();
		a[i][j]=ch=='Y';
	}
	int l=1,r=n,res=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))l=mid+1,res=mid;
		else r=mid-1;
	}
	printf("%d\n",res);
	return 0;
}
/*
3 0
YYY
YYY
YYY

*/