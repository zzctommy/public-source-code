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
const int N=100005;
const int M=30005;
const int S=600;
template<int N>struct Bitset{

typedef unsigned long long ull;
static const int O=(N-1)/64+1;
static const ull ULL_MAX=18446744073709551615ull;
ull a[O];
Bitset(){memset(a,0,sizeof(a));}
void reset(){memset(a,0,sizeof(a));}
void set(int x){a[(x>>6)]|=1ull<<(x&63);}
Bitset&operator |= (const Bitset&t){
	for(int i=0;i<O;++i)a[i]|=t.a[i];
	return *this;
}
Bitset operator | (const Bitset&t){
	Bitset res;
	for(int i=0;i<O;++i)res.a[i]=a[i]|t.a[i];
	return res;
}
int count(){
	int res=0;
	for(int i=0;i<O;++i)res+=__builtin_popcountll(a[i]);
	return res;
}
int mex(){
	for(int i=0;i<O;++i)if(a[i]<ULL_MAX)
		for(int j=0;j<64;++j)if(!(a[i]>>j&1ull))return (i<<6)|j;
	return N+1;
}

};
Bitset<M>bs[N/S+5][N/S+5];
int n,m,f,lastans,a[N];
int siz[N],fa[N],top[N],son[N],dep[N],mxd[N];
int id[N],tot,up[N];
int et,hed[N];
struct edge{int nx,to;}e[N<<1]; 
void adde(int u,int v){e[++et].nx=hed[u],e[et].to=v,hed[u]=et;}
void dfs1(int u,int ft){
	mxd[u]=dep[u],siz[u]=1;
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		dep[v]=dep[u]+1,dfs1(v,u);
		fa[v]=u,siz[u]+=siz[v];
		ckmax(mxd[u],mxd[v]);
		if(siz[v]>siz[son[u]])son[u]=v;
	}
	if(u==1||mxd[u]-dep[u]>S)id[u]=++tot,mxd[u]=dep[u];
}
void dfs2(int u,int tp){
	top[u]=tp;
	if(son[u])dfs2(son[u],tp);
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
void dfs(int u,int ft,int lst){
	if(id[u]){
		up[u]=lst,bs[id[u]][id[u]].set(a[u]);
		if(lst){
			int now=u;
			while(now!=lst)bs[id[u]][id[lst]].set(a[now]),now=fa[now];
			now=up[lst];
			while(now)(bs[id[u]][id[now]]=bs[id[u]][id[lst]])|=bs[id[lst]][id[now]],now=up[now];
		}
	}
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		dfs(v,u,id[u]?u:lst);
	}
}
int LCA(int x,int y){
	while(top[x]!=top[y])dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
	return dep[x]<dep[y]?x:y;
}
signed main(){
	n=read(),m=read(),f=read();
	rep(i,1,n)a[i]=read();
	rep(i,2,n){
		int x=read(),y=read();
		adde(x,y),adde(y,x);
	}
	dep[1]=1,dfs1(1,0),dfs2(1,1),dfs(1,0,0);
	while(m--){
		int q=read(),mex,sum;
		static Bitset<M>ans;
		ans.reset();
		rep(i,1,q){
			int x=read(),y=read();
			if(f)x^=lastans,y^=lastans;
			int lca=LCA(x,y);
			ans.set(a[lca]);
			while(!id[x]&&x!=lca)ans.set(a[x]),x=fa[x];
			while(!id[y]&&y!=lca)ans.set(a[y]),y=fa[y];
			if(x!=lca){
				int now=x;
				while(dep[up[now]]>=dep[lca])now=up[now];
				ans|=bs[id[x]][id[now]];
				while(now!=lca)ans.set(a[now]),now=fa[now];
			}
			if(y!=lca){
				int now=y;
				while(dep[up[now]]>=dep[lca])now=up[now];
				ans|=bs[id[y]][id[now]];
				while(now!=lca)ans.set(a[now]),now=fa[now];
			}
		}
		lastans=(sum=ans.count())+(mex=ans.mex()),printf("%d %d\n",sum,mex); 
	}
}