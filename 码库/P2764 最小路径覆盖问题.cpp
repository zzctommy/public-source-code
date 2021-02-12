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

const int N=320;
const int M=2*(N+6000);
const int inf=0x3f3f3f3f;
int n,m,nxt[N],pre[N];
int dep[N],S,T,mf,ND,cur[N];
int hed[N],et=1;
struct edge{int to,nx,fl;}e[M];
inline void addedge(int u,int v,int fl){e[++et].nx=hed[u],e[et].to=v,e[et].fl=fl,hed[u]=et;}
inline void adde(int u,int v,int fl){addedge(u,v,fl),addedge(v,u,0);}
bool bfs(){
	assert(ND>0);
	queue<int>q;
	for(int i=1;i<=ND;++i)dep[i]=0,cur[i]=hed[i];
	q.push(S),dep[S]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=hed[u];i;i=e[i].nx){
			int v=e[i].to;
			if(e[i].fl&&!dep[v])dep[v]=dep[u]+1,q.push(v);
		}
	}
	return dep[T]>0;
}
int dfs(int u,int fl){
	if(u==T)return fl;
	int rl,us=0;
	for(int i=cur[u];i;i=e[i].nx){
		int v=e[i].to;cur[u]=i;
		if(e[i].fl&&dep[v]==dep[u]+1){
			rl=dfs(v,min(fl-us,e[i].fl));
			if(rl)e[i].fl-=rl,e[i^1].fl+=rl,us+=rl;
			if(us==fl)break;
		}
	}
	return us;
}
signed main(){
	n=read(),m=read(),S=n*2+1,T=S+1,ND=T;
	rep(i,1,n)adde(S,i,1),adde(i+n,T,1);
	rep(i,1,m){
		int x=read(),y=read();
		adde(x,y+n,1);
	}
	while(bfs())mf+=dfs(S,inf);
	for(int i=2;i<=et;i+=2){
		if(e[i].to==S||e[i].to==T||e[i^1].to==S||e[i^1].to==T)continue;
		if(e[i^1].fl)nxt[e[i^1].to]=e[i].to-n,pre[e[i].to-n]=e[i^1].to;
	}
	for(int i=1;i<=n;++i){
		if(pre[i])continue;
		for(int j=i;j;j=nxt[j])printf("%d ",j);
		puts("");
	}
	printf("%d\n",n-mf);
}