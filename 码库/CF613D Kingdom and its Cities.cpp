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
int n,q,a[N],m,ans;
int stk[N],top;
bool book[N];
vector<int>g[N];
int hed[N],et;
struct edge{int nx,to;}e[N<<1];
void adde(int u,int v){e[++et].nx=hed[u],e[et].to=v,hed[u]=et;}
namespace Tree{
int fa[N],top[N],son[N],dep[N],siz[N],dfn[N],tmr;
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
		if(v!=fa[u]&&v!=son[u])dfs2(v,v);
	}
}
int LCA(int x,int y){
	while(top[x]!=top[y])dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
	return dep[x]<dep[y]?x:y;
}
void init(){dfs1(1,0),dfs2(1,1);}
}
using Tree::LCA;
using Tree::dfn;
using Tree::dep;
using Tree::fa;
inline bool cmp(int a,int b){return dfn[a]<dfn[b];}
void dfs(int u){
	int cnt=0;
	for(auto v:g[u]){
		dfs(v);
		if(book[v])++cnt;
		book[v]=0;
	}
	if(book[u])ans+=cnt;
	else{
		if(cnt==1)book[u]=1;
		else if(cnt>1)++ans;
	}
	g[u].clear();
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
		rep(i,1,m)a[i]=read(),book[a[i]]=1;
		sort(a+1,a+m+1,cmp);
		bool flg=1;
		rep(i,1,m)if(book[a[i]]&&book[fa[a[i]]]){flg=0;break;}
		if(!flg){
			puts("-1");
			rep(i,1,m)book[a[i]]=0;
			continue;
		}
		stk[top=1]=a[1];
		rep(i,2,m){
			int lca=LCA(stk[top],a[i]);
			while(top>1&&dep[stk[top-1]]>=dep[lca])g[stk[top-1]].pb(stk[top]),--top;
			if(lca!=stk[top])g[lca].pb(stk[top]),stk[top]=lca;
			stk[++top]=a[i];
		}
		while(--top)g[stk[top]].pb(stk[top+1]);
		ans=0,dfs(stk[1]),printf("%d\n",ans);
		book[stk[1]]=0;
	}
}