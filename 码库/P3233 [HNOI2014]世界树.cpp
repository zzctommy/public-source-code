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
const int N=300005;
int n,q,m,h[N],d[N],f[N],ans[N];
bool book[N];
vector<int>g[N],e[N];
int bz[20][N],dep[N],dfn[N],tmr,siz[N];
void dfs(int u,int ft){
	dep[u]=dep[ft]+1,bz[0][u]=ft,dfn[u]=++tmr,siz[u]=1;
	for(int i=1;1<<i<dep[u];++i)bz[i][u]=bz[i-1][bz[i-1][u]];
	for(int v:e[u])if(v!=ft)dfs(v,u),siz[u]+=siz[v];
}
int LCA(int x,int y){
	if(dep[x]<dep[y])x^=y^=x^=y;
	int del=dep[x]-dep[y];
	for(int i=19;i>=0;--i)if(del>>i&1)x=bz[i][x];
	if(x==y)return x;
	for(int i=19;i>=0;--i)if(bz[i][x]!=bz[i][y])x=bz[i][x],y=bz[i][y];
	return bz[0][x];
}
int kthanc(int x,int k){
	for(int i=19;i>=0;--i)if(k>>i&1)x=bz[i][x];
	return x;
}
inline bool cmp(const int&a,const int&b){return dfn[a]<dfn[b];}
int build(){
	static int stk[N],top,a[N];
	memcpy(a,h,(n+1)<<2);
	sort(a+1,a+m+1,cmp);
	stk[top=1]=a[1];
	rep(i,2,m){
		int lca=LCA(stk[top],a[i]);
		while(top>1&&dep[stk[top-1]]>=dep[lca])g[stk[top-1]].pb(stk[top])
		/*,cerr<<"edge:"<<stk[top-1]<<' '<<stk[top]<<'\n'*/,--top;
		if(stk[top]!=lca)g[lca].pb(stk[top])/*,cerr<<"edge:"<<lca<<' '<<stk[top]<<'\n'*/,stk[top]=lca;
		stk[++top]=a[i];
	}
	while(--top)g[stk[top]].pb(stk[top+1])/*,cerr<<"edge:"<<stk[top]<<' '<<stk[top+1]<<'\n'*/;
	return stk[1];
}
void dfs1(int u){
	if(book[u])f[u]=u,d[u]=0;
	else f[u]=d[u]=n+1;
	for(int v:g[u]){
		dfs1(v);
		if(ckmin(d[u],d[v]+dep[v]-dep[u]))f[u]=f[v];
		else if(d[u]==d[v]+dep[v]-dep[u])ckmin(f[u],f[v]);
	}
}
void dfs2(int u){
	for(int v:g[u]){
		if(ckmin(d[v],d[u]+dep[v]-dep[u]))f[v]=f[u];
		else if(d[v]==d[u]+dep[v]-dep[u])ckmin(f[v],f[u]);
		dfs2(v);
	}
}
void dfs3(int u){
	ans[f[u]]+=siz[u];
	for(int v:g[u])ans[f[u]]-=siz[kthanc(v,dep[v]-dep[u]-1)],dfs3(v);
}
void dfs4(int u){
	for(int v:g[u]){
		if(f[u]==f[v])ans[f[u]]+=siz[kthanc(v,dep[v]-dep[u]-1)]-siz[v];
		else{
			int o=dep[f[v]]+dep[u]-d[u],t=v;
			if(o&1)o=(o+1)>>1;
			else o=f[v]<f[u]?(o>>1):(o>>1)+1;
			for(int i=19;i>=0;--i)if(dep[bz[i][t]]>=o)t=bz[i][t];
			ans[f[u]]+=siz[kthanc(v,dep[v]-dep[u]-1)]-siz[t];
			ans[f[v]]+=siz[t]-siz[v];
		}
		dfs4(v);
	}
	g[u].clear(),f[u]=d[u]=0;
}
signed main(){
	n=read();
	rep(i,2,n){
		int x=read(),y=read();
		e[x].pb(y),e[y].pb(x);
	}
	dfs(1,0);
	for(q=read();q;--q){
		m=read();
		rep(i,1,m)h[i]=read(),book[h[i]]=1;
		int rt=build();
		dfs1(rt),dfs2(rt);
		ans[f[rt]]+=siz[1]-siz[rt];
		dfs3(rt),dfs4(rt);
		rep(i,1,m)printf("%d%c",ans[h[i]]," \n"[i==m]);
		rep(i,1,m)book[h[i]]=ans[h[i]]=0;
	}
}