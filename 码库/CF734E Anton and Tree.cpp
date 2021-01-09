//Orz cyn2006
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
const int N=200005;
int n,c[N],U[N],V[N],id[N],cnt,f[N],ans;
struct edge{int nx,to;}e[N<<1];
int et,hed[N];
void adde(int u,int v){e[++et].nx=hed[u],e[et].to=v,hed[u]=et;}
void dfs1(int u,int ft){
	if(c[u]!=c[ft])id[u]=++cnt;
	else id[u]=id[ft];
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		dfs1(v,u);
	}
}
void dfs2(int u,int ft){
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		dfs2(v,u),ckmax(ans,f[v]+f[u]+1),ckmax(f[u],f[v]+1);
	}
}
signed main(){
	n=read();
	rep(i,1,n)c[i]=read();
	rep(i,1,n-1)
		U[i]=read(),V[i]=read(),adde(U[i],V[i]),adde(V[i],U[i]);
	c[0]=-1,dfs1(1,0);
	memset(hed,0,sizeof(hed)),et=0;
	rep(i,1,n-1)if(id[U[i]]!=id[V[i]])adde(id[U[i]],id[V[i]]),adde(id[V[i]],id[U[i]]);
	dfs2(1,0);
	printf("%d\n",(ans+1)>>1);
	return 0;
}