#include<bits/stdc++.h>
#include "rts.h"
using namespace std;
#define pb push_back
#define sz(v) (int)v.size()
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##dnd;--i)
template<class T>inline bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>inline bool ckmin(T&x,T y){return x>y?x=y,1:0;}
typedef long long LL;
typedef double db;
const int N=300005;
int rd,a[N];
bool vis[N];

struct RAND{
const int basic=(1<<30)-1;
unsigned long long sa,sb,sc;
RAND(){
	srand(time(0));
	for(int i=0,up=::rand()%100;i<=up;++i)::rand();
	srand(::rand()^clock()),sa=1ull*::rand()*::rand()*::rand();
	for(int i=0,up=::rand()%100;i<=up;++i)::rand();
	srand(::rand()^clock()),sb=1ull*::rand()*::rand()*::rand();
	for(int i=0,up=::rand()%100;i<=up;++i)::rand();
	srand(::rand()^clock()),sc=1ull*::rand()*::rand()*::rand();
}
int rand(){
	sa^=sa<<32,sa^=sa>>13,sa^=sa<<1;
	unsigned long long t=sa;
	sa=sb,sb=sc,sc^=t^sa;
	return sc&basic;
}
int rad(int l,int r){return rand()%(r-l+1)+l;}
}mk;

namespace data3{

void cov(int x,int y){
	vis[x]=1;
	while(x!=y)rd=explore(x,y),vis[x=rd]=1;
}
void main(const int&n){
	int l=1,r=1;
	rep(i,2,n){
		int u=a[i];
		if(vis[u])continue;
		if(!vis[rd=explore(l,u)])cov(rd,u),l=u;
		else cov(r,u),r=u;
	}
}

}

namespace std{

const db alpha=0.75;
vector<int>e[N],to[N];
int fa[N],mx[N],rt,tsize,siz[N],reb,vt[N],sz[N],root;//sz是分治树的大小，vt是分治树上的父亲
bool used[N];
void getrt(int u,int ft){//找重心
	siz[u]=1,mx[u]=0;
	for(int i=0,up=sz(e[u]);i<up;++i){
		int v=e[u][i];
		if(v==ft||used[v])continue;
		getrt(v,u),siz[u]+=siz[v];
		ckmax(mx[u],siz[v]);
	}
	ckmax(mx[u],tsize-siz[u]);
	if(mx[u]<mx[rt])rt=u;
}
void pia(int u){//拍扁，同时给要重构的点打标记
	++tsize,used[u]=0;
	for(int v:to[u])pia(v);
	to[u].clear();
}
void dfs_build(int u){//普通建立点分树
	used[u]=1,sz[u]=1;
	for(int i=0,up=sz(e[u]);i<up;++i){
		int v=e[u][i];
		if(used[v])continue;
		rt=0,tsize=siz[v],getrt(v,u);
		int tmp=rt;//一定要存一下，rt在变
		to[u].pb(rt),vt[rt]=u,dfs_build(rt),sz[u]+=sz[tmp];
	}
}
void rebuild(int u){//重构
	rt=0,tsize=0,pia(u);
	getrt(u,0);
	if(u==root)root=rt;
	if(vt[u])
		for(int i=0,up=sz(to[vt[u]]);i<up;++i)if(to[vt[u]][i]==u)to[vt[u]][i]=rt;
	vt[rt]=vt[u];
	dfs_build(rt);
}
void dfs_ins(int x,int ft){//点分树上插入一条边，ft已经在树上
	used[x]=vis[x]=1;
	fa[x]=vt[x]=ft,to[ft].pb(x),e[ft].pb(x),e[x].pb(ft);
	for(int i=x;i;i=vt[i])++sz[i];
	reb=0;
	for(int i=x;vt[i];i=vt[i])if(sz[i]>1.*sz[vt[i]]*alpha)reb=vt[i];
	if(reb)rebuild(reb);
}
void solve(int u,int t){//找到那个点并且加边
	rd=explore(u,t);
	if(!vis[rd]){
		int x=rd;
		dfs_ins(x,u);
		while(x!=t){
			rd=explore(x,t);
			dfs_ins(rd,x);
			x=rd;
		}
		return;
	}
	while(vt[rd]!=u)rd=vt[rd];
	solve(rd,t);
}
void main(const int&n){
	vis[1]=1,mx[rt=0]=n,sz[1]=1,used[1]=1,root=1;
	rep(i,2,n){
		int u=a[i];
		if(vis[u])continue;
		solve(root,u);
	}
}
}

void play(int n,int T,int dataType){
	vis[1]=1;
	rep(i,2,n)a[i]=i;
	rep(i,2,n)swap(a[i],a[mk.rad(2,n)]);//随机操作序列
	if(dataType==3)data3::main(n);
	else std::main(n);
}

