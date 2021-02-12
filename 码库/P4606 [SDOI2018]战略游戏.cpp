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
int n,m,tot;

namespace Tree{

struct edge{int nx,to;}e[N<<1];
int et,hed[N];
void adde(int u,int v){e[++et].nx=hed[u],e[et].to=v,hed[u]=et;}
int bz[20][N],dep[N],dfn[N],tmr,len[N];
void dfs(int u,int ft){
	dep[u]=dep[bz[0][u]=ft]+1,dfn[u]=++tmr;
	for(int i=1;1<<i<=dep[u];++i)
		bz[i][u]=bz[i-1][bz[i-1][u]];
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		len[v]=len[u]+(v<=n),dfs(v,u);
	}
}
void init(){dfs(1,0);}
int LCA(int x,int y){
	if(dep[x]<dep[y])x^=y^=x^=y;
	for(int i=19,dta=dep[x]-dep[y];i>=0;--i)
		if(dta>>i&1)x=bz[i][x];
	if(x==y)return x;
	for(int i=19;i>=0;--i)
		if(bz[i][x]!=bz[i][y])x=bz[i][x],y=bz[i][y];
	return bz[0][x];
}
inline bool cmp(const int&a,const int&b){return dfn[a]<dfn[b];}
void solve(){
	static int m,h[N],res,stk[N],top;
	m=read(),res=0;
	rep(i,1,m)h[i]=read();
	sort(h+1,h+m+1,cmp);
	stk[top=1]=h[1];
	for(int i=2;i<=m;++i){
		int lca=LCA(h[i],stk[top]);
		while(dep[stk[top-1]]>=dep[lca])res+=len[stk[top]]-len[stk[top-1]],--top;
		if(stk[top]!=lca)res+=len[stk[top]]-len[lca],stk[top]=lca;
		stk[++top]=h[i];
	}
	while(--top)res+=len[stk[top+1]]-len[stk[top]];
	res+=stk[1]<=n,res-=m;
	printf("%d\n",res);
}
void clear(){
	memset(hed,0,(tot+1)<<2);
	memset(bz,0,sizeof(bz));
	et=tmr=0;
}
}
namespace cac{

int dfn[N],low[N],tmr,stk[N],top;
struct edge{int nx,to;}e[N<<1];
int et,hed[N];
void adde(int u,int v){e[++et].nx=hed[u],e[et].to=v,hed[u]=et;}
void tarjan(int u){
	stk[++top]=u,dfn[u]=low[u]=++tmr;
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;
		if(!dfn[v]){
			tarjan(v),ckmin(low[u],low[v]);
			if(low[v]==dfn[u]){
				++tot,Tree::adde(tot,u),Tree::adde(u,tot);
				while(stk[top+1]!=v)
					Tree::adde(tot,stk[top]),Tree::adde(stk[top],tot),--top;
			}
		}else ckmin(low[u],dfn[v]);
	}
}
void init(){tot=n,tarjan(1);}
void clear(){
	memset(low,0,(n+1)<<2);
	memset(dfn,0,(n+1)<<2);
	memset(hed,0,(n+1)<<2);
	memset(stk,0,(n+1)<<2);
	top=et=tmr=0;
}
}
void Main(){
	n=read(),m=read();
	rep(i,1,m){
		int x=read(),y=read();
		cac::adde(x,y),cac::adde(y,x);
	}
	cac::init(),Tree::init();
	for(int q=read();q;--q)Tree::solve();
	cac::clear(),Tree::clear();
}
signed main(){for(int T=read();T;--T)Main();}