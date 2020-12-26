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
const int N=40005;
const int S=800;
int n,m,lsh[N],len,a[N],lastans;
int top[N],fa[N],dep[N],siz[N],son[N];
int id[N],tot,mxd[N],up[N];
bitset<N>bs[N/S+5][N/S+5];
int hed[N],et;
struct edge{int nx,to;}e[N<<1];
void adde(int u,int v){e[++et].nx=hed[u],e[et].to=v,hed[u]=et;}
void dfs1(int u,int ft){
	siz[u]=1,mxd[u]=dep[u];
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		dep[v]=dep[u]+1,dfs1(v,u),siz[u]+=siz[v],fa[v]=u;
		ckmax(mxd[u],mxd[v]);
		if(siz[v]>siz[son[u]])son[u]=v;
	}
	if(u==1||mxd[u]-dep[u]>S)mxd[u]=dep[u],id[u]=++tot;
}
void dfs2(int u,int tp){
	top[u]=tp;
	if(son[u])dfs2(son[u],tp);
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
void dfs(int u,int ft,int lst){
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		if(id[u]){
			up[u]=lst,bs[id[u]][id[u]].set(a[u]);
			int now=u;
			while(now!=fa[lst])bs[id[u]][id[lst]].set(a[now]),now=fa[now];
			now=up[lst];
			while(now)(bs[id[u]][id[now]]|=bs[id[u]][id[lst]])|=bs[id[lst]][id[now]],now=up[now];
			dfs(v,u,u);
		}else dfs(v,u,lst);
	}
}
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
signed main(){
	n=read(),m=read();
	rep(i,1,n)a[i]=lsh[++len]=read();
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	rep(i,1,n)a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
	rep(i,2,n){
		int x=read(),y=read();
		adde(x,y),adde(y,x);
	}
	dep[1]=1,dfs1(1,0),dfs2(1,1),dfs(1,0,0);
	while(m--){
		static bitset<N>ans;
		int x=read()^lastans,y=read(),lca=LCA(x,y);
		ans.reset(),ans.set(a[lca]);
		while(!id[x]&&x!=lca)ans.set(a[x]),x=fa[x];
		while(!id[y]&&y!=lca)ans.set(a[y]),y=fa[y];
		if(x!=lca){
			int now=x;
			while(up[now]&&dep[up[now]]>dep[lca])now=up[now];
			ans|=bs[id[x]][id[now]];
			while(now!=lca)ans.set(a[now]),now=fa[now]; 
		}
		if(y!=lca){
			int now=y;
			while(up[now]&&dep[up[now]]>dep[lca])now=up[now];
			ans|=bs[id[y]][id[now]];
			while(now!=lca)ans.set(a[now]),now=fa[now];
		}
		printf("%d\n",lastans=ans.count());
	}
}