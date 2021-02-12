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
int n,q,a[N],rt;
LL S,D,R1[N],R2[N],R3[N],sum[N];
int fa[N],top[N],son[N],dep[N],siz[N];
int hed[N],et;
struct edge{int nx,to;}e[N<<1];
void adde(int u,int v){e[++et].nx=hed[u],e[et].to=v,hed[u]=et;}

namespace Tree{
void dfs1(int u,int ft){
	siz[u]=1,dep[u]=dep[ft]+1,sum[u]=a[u];
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		fa[v]=u,dfs1(v,u),siz[u]+=siz[v],sum[u]+=sum[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
	D+=sum[u]*(S-sum[u]);
}
void dfs2(int u,int tp){
	top[u]=tp;
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
int dis(int x,int y){return dep[x]+dep[y]-(dep[LCA(x,y)]<<1);}
}
using Tree::LCA;
using Tree::dis;

namespace DFZ{
int siz[N],mx[N],tsiz,vt[N];
bool used[N];
void getrt(int u,int ft){
	siz[u]=1,mx[u]=0;
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft||used[v])continue;
		getrt(v,u),siz[u]+=siz[v];
		ckmax(mx[u],siz[v]);
	}
	ckmax(mx[u],tsiz-siz[u]);
	if(mx[u]<mx[rt])rt=u;
}
bool qwq[N];
void solve(int x){
	static int cnt=0;
	used[x]=1;
	for(int i=x;i;i=vt[i]){
		R1[i]+=a[x]*dis(i,x),R3[i]+=a[x];
		if(vt[i])R2[i]+=a[x]*dis(vt[i],x);
	}
	for(int i=hed[x];i;i=e[i].nx){
		int y=e[i].to;if(used[y])continue;
		tsiz=siz[y],rt=0,getrt(y,x),vt[rt]=x,solve(rt);
	}
}
LL calc(int x){
	LL res=R1[x];
	for(int i=x;vt[i];i=vt[i])
		res+=R1[vt[i]]-R2[i]+(R3[vt[i]]-R3[i])*dis(vt[i],x);
	return res;
}
void upd(int x,int y){
	for(int i=x;i;i=vt[i]){
		R1[i]+=y*dis(i,x),R3[i]+=y;
		if(vt[i])R2[i]+=y*dis(vt[i],x);
	}
}

void change(int x,int y){
	D+=calc(x)*(y-a[x]),S+=y-a[x],upd(x,y-a[x]),a[x]=y;
}
LL query(int x){return S*(calc(x)+S)-D;}
void build(){mx[rt=0]=tsiz=n,getrt(1,0),solve(rt);}
}
signed main(){
	n=read(),q=read();
	rep(i,2,n){
		int x=read(),y=read();
		adde(x,y),adde(y,x);
	}
	rep(i,1,n)a[i]=read(),S+=a[i];
	Tree::dfs1(1,0),Tree::dfs2(1,1);
	DFZ::build();
	while(q--){
		int op=read(),x=read();
		if(op==1)DFZ::change(x,read());
		else printf("%lld\n",DFZ::query(x));
	}
	return 0;
}