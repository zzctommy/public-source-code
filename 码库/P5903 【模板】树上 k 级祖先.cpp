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

#define ui unsigned int
ui s;
inline ui get(ui x) {
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x; 
}
const int N=500005;
int n,q,fa[N],rt,lstans,lg[N];
LL ans;
int hed[N],et,nx[N],to[N];
int son[N],len[N],bz[20][N],dep[N],top[N];
int *dw[N],*up[N],pool[N*3],*mem=pool;
inline void adde(int u,int v){nx[++et]=hed[u],to[et]=v,hed[u]=et;}
void dfs1(int u){
	dep[u]=dep[bz[0][u]=fa[u]]+1;
	for(int i=1;1<<i<dep[u];++i)bz[i][u]=bz[i-1][bz[i-1][u]];
	for(int i=hed[u];i;i=nx[i]){
		int v=to[i];
		dfs1(v);
		if(len[v]>len[son[u]])son[u]=v;
	}
	len[u]=len[son[u]]+1;
}
void dfs2(int u,int tp){
	top[u]=tp;
	if(son[u])dfs2(son[u],tp);
	for(int i=hed[u];i;i=nx[i]){
		int v=to[i];if(v==son[u])continue;
		dfs2(v,v);
	}
	if(top[u]==u){
		dw[u]=mem;
		for(int i=u;i;i=son[i])*mem++=i;
		up[u]=mem;
		for(int i=u,j=0;j<=len[u]&&i;++j,i=fa[i])*mem++=i;
	}
}
int kthanc(int x,int k){
	if(!k)return x;
	int y=top[bz[lg[k]][x]];
	if(dep[x]-dep[y]>=k)return dw[y][dep[x]-k-dep[y]];
	else return up[y][dep[y]-dep[x]+k];
}
signed main(){
	cin>>n>>q>>s;
	rep(i,1,n){
		fa[i]=read();
		if(!fa[i])rt=i;
		else adde(fa[i],i);
	}
	lg[0]=-1;rep(i,1,n)lg[i]=lg[i>>1]+1;
	dfs1(rt),dfs2(rt,rt);
	rep(t,1,q){
		int x=(get(s)^lstans)%n+1,y=(get(s)^lstans)%dep[x];
		ans^=1ll*(lstans=kthanc(x,y))*t;
	}
	cout<<ans<<'\n';
}