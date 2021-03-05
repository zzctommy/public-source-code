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

const int N=100005;
int n;
struct edge{int nx,to;}e[N<<1];
int hed[N],et;
inline void adde(int u,int v){e[++et].nx=hed[u],e[et].to=v,hed[u]=et;}
LL *f[N],*g[N],pool[N<<2],*mem=pool,ans;
int son[N],len[N];
void dfs1(int u,int ft){
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		dfs1(v,u);
		if(len[v]>len[son[u]])son[u]=v;
	}
	len[u]=len[son[u]]+1;
}
void dfs2(int u,int ft){
	if(son[u])f[son[u]]=f[u]+1,g[son[u]]=g[u]-1,dfs2(son[u],u);
	f[u][0]=1,ans+=g[u][0];
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft||v==son[u])continue;
		f[v]=mem,mem+=len[v]+1,mem+=len[v]-1,g[v]=mem,mem+=len[v]+1;
		dfs2(v,u);
		for(int j=0;j<len[v];++j){
			ans+=g[u][j+1]*f[v][j];
			if(j)ans+=f[u][j-1]*g[v][j];
		}
		for(int j=0;j<len[v];++j){
			g[u][j+1]+=f[u][j+1]*f[v][j];
			if(j)g[u][j-1]+=g[v][j];
			f[u][j+1]+=f[v][j];
		}
	}
}
signed main(){
	n=read();
	rep(i,2,n){
		int x=read(),y=read();
		adde(x,y),adde(y,x);
	}
	dfs1(1,0);
	f[1]=mem,mem+=len[1]+1,mem+=len[1]-1,g[1]=mem,mem+=len[1]+1;
	dfs2(1,0);
	cout<<ans<<'\n';
}