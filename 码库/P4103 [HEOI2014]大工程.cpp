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

const int N=1000005;
int n,q,m,h[N],ans2,ans3,f[N];
LL dp[N],ans1;
int sz[N];
bool book[N];
int et,hed[N];
struct edge{int nx,to;}e[N<<1];
void adde(int u,int v){e[++et].nx=hed[u],e[et].to=v,hed[u]=et;}
vector<int>G[N];
namespace Tree{
int top[N],fa[N],dep[N],siz[N],tmr,dfn[N],son[N];
void dfs1(int u,int ft){
	siz[u]=1,dep[u]=dep[ft]+1;
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		fa[v]=u,dfs1(v,u),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp){
	top[u]=tp,dfn[u]=++tmr;
	if(son[u])dfs2(son[u],tp);
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
int LCA(int x,int y){
	while(top[x]!=top[y])dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
	return dep[x]<dep[y]?x:y;
}
int dis(int x,int y){return dep[x]+dep[y]-(dep[LCA(x,y)]<<1);}
void init(){dfs1(1,0),dfs2(1,1);}

}
using Tree::LCA;
using Tree::dfn;
using Tree::dep;
using Tree::dis;

inline bool cmp(const int&a,const int&b){return dfn[a]<dfn[b];}
int build(int*h,int m){
	static int stk[N],top,a[N];
	memcpy(a,h,(m+1)<<2);
	sort(a+1,a+m+1,cmp);
	stk[top=1]=a[1];
	rep(i,2,m){
		int lca=LCA(stk[top],a[i]);
		while(top>1&&dep[stk[top-1]]>=dep[lca])G[stk[top-1]].pb(stk[top]),--top;
		if(lca!=stk[top])G[lca].pb(stk[top]),stk[top]=lca;
		stk[++top]=a[i];
	}
	while(--top)G[stk[top]].pb(stk[top+1]);
	return stk[1];
}
void dfs1(int u){
	if(book[u])sz[u]=1;
	else sz[u]=0;
	for(int v:G[u])dfs1(v),sz[u]+=sz[v];
}
void dfs2(int u){
	if(book[u])ans1+=dp[u];
	for(int v:G[u]){
		dp[v]=dp[u]+1ll*(m-2*sz[v])*(dep[v]-dep[u]);
		dfs2(v);
	}
}
void dfs3(int u){
	f[u]=0;
	for(int v:G[u]){
		dfs3(v);
		ckmax(ans3,f[u]+f[v]+dep[v]-dep[u]);
		ckmax(f[u],f[v]+dep[v]-dep[u]);
	}
}
void dfs4(int u){
	if(book[u])f[u]=0;
	else f[u]=1919810;
	for(int v:G[u]){
		dfs4(v);
		ckmin(ans2,f[u]+f[v]+dep[v]-dep[u]);
		ckmin(f[u],f[v]+dep[v]-dep[u]);
	}
	dp[u]=book[u]=0,G[u].clear();
}
signed main(){
	n=read();
	rep(i,2,n){
		int x=read(),y=read();
		adde(x,y),adde(y,x);
	}
	Tree::init();
	for(q=read();q;--q){
		m=read();
		rep(i,1,m)h[i]=read(),book[h[i]]=1;
		int rt=build(h,m);
		rep(i,1,m)dp[rt]+=dep[h[i]]-dep[rt];
		ans1=0,ans2=n,ans3=0;
		dfs1(rt),dfs2(rt),dfs3(rt),dfs4(rt);
		printf("%lld %d %d\n",ans1/2ll,ans2,ans3);
	}
}