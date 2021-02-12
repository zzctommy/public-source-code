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
#define mod 998244353
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}
vector<int>e1[N],e2[N],e[N];
int n,m,U[20],V[20],num,tr[N],tot,ans;
int fa[N],top[N],son[N],siz[N],dep[N],dfn[N],tmr;
int fir[N][2],dp[N][2],fa2[N],a0[N][2],a1[N][2];
bool vis[N],bok[N];

void dfs1(int u){
	vis[u]=1,siz[u]=1;
	for(int v:e[u]){
		if(vis[v]&&dep[v]>dep[u])U[num]=u,V[num++]=v,bok[u]=bok[v]=1;
		else if(!vis[v]){
			e1[u].pb(v),dep[v]=dep[u]+1,fa[v]=u,dfs1(v),siz[u]+=siz[v];
			if(siz[v]>siz[son[u]])son[u]=v;
		}
	}
}
void dfs2(int u,int tp){
	fir[u][0]=fir[u][1]=1;
	dfn[u]=++tmr,top[u]=tp;
	if(son[u]){
		dfs2(son[u],tp),bok[u]|=bok[son[u]];
		if(!bok[son[u]]){
			fir[u][0]=1ll*fir[u][0]*(fir[son[u]][0]+fir[son[u]][1])%mod;
			fir[u][1]=1ll*fir[u][1]*fir[son[u]][0]%mod;
		}
	}
	for(int v:e1[u]){
		if(v==son[u])continue;
		dfs2(v,v),bok[u]|=bok[v];
		if(!bok[v]){
			fir[u][0]=1ll*fir[u][0]*(fir[v][0]+fir[v][1])%mod;
			fir[u][1]=1ll*fir[u][1]*fir[v][0]%mod;
		}
	}
}
inline int LCA(int x,int y){
	while(top[x]!=top[y])dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
	return dep[x]<dep[y]?x:y;
}
inline bool cmp(const int&a,const int&b){return dfn[a]<dfn[b];}
void build(){
	static int a[N],top,stk[N],m;
	memset(vis,0,sizeof(vis));
	for(int i=0;i<num;++i){
		if(!vis[U[i]])vis[U[i]]=1,a[++m]=U[i];
		if(!vis[V[i]])vis[V[i]]=1,a[++m]=V[i];
	}
	if(!vis[1])a[++m]=1;
	sort(a+1,a+m+1,cmp),stk[top=1]=a[1];
	for(int i=1;i<=m;++i)tr[++tot]=a[i];
	rep(i,2,m){
		int lca=LCA(a[i],stk[top]);tr[++tot]=lca;
		while(top>1&&dep[stk[top-1]]>=dep[lca])
			e2[stk[top-1]].pb(stk[top]),fa2[stk[top]]=stk[top-1],--top;
		if(stk[top]!=lca)e2[lca].pb(stk[top]),fa2[stk[top]]=lca,stk[top]=lca;
		stk[++top]=a[i];
	}
	while(--top)e2[stk[top]].pb(stk[top+1]),fa2[stk[top+1]]=stk[top];
}
void dfs4(int u,int av){
	dp[u][0]=dp[u][1]=1;
	for(int v:e1[u]){
		if(v==av)continue;
		dfs4(v,-1);
		dp[u][0]=1ll*dp[u][0]*(dp[v][0]+dp[v][1])%mod;
		dp[u][1]=1ll*dp[u][1]*dp[v][0]%mod;
	}
}
void calc(int u){
	int x=u;
	a0[u][0]=a1[u][1]=1;
	while(fa[x]!=fa2[u]){
		dfs4(fa[x],x);
		int a10=a1[u][0],a11=a1[u][1],a00=a0[u][0],a01=a0[u][1];
		a0[u][0]=1ll*dp[fa[x]][0]*(a00+a10)%mod;
		a0[u][1]=1ll*dp[fa[x]][0]*(a01+a11)%mod;
		a1[u][0]=1ll*dp[fa[x]][1]*a00%mod;
		a1[u][1]=1ll*dp[fa[x]][1]*a01%mod;
		x=fa[x];
	}
	int a10=a1[u][0],a11=a1[u][1],a00=a0[u][0],a01=a0[u][1];
	a0[u][0]=(a00+a10)%mod;
	a0[u][1]=(a01+a11)%mod;
	a1[u][0]=a00;
	a1[u][1]=a01;
}
void dfs3(int u){
	calc(u);
	for(int v:e2[u])dfs3(v);
}
void dfs5(int u){
	for(int v:e2[u]){
		dfs5(v);
		dp[u][0]=1ll*dp[u][0]*(1ll*dp[v][0]*a0[v][0]%mod+1ll*dp[v][1]*a0[v][1]%mod)%mod;
		dp[u][1]=1ll*dp[u][1]*(1ll*dp[v][0]*a1[v][0]%mod+1ll*dp[v][1]*a1[v][1]%mod)%mod;
	}
}
signed main(){
	n=read(),m=read();
	rep(i,1,m){
		int x=read(),y=read();
		e[x].pb(y),e[y].pb(x);
	}
	dfs1(1),dfs2(1,1),build();
	dfs3(1);
	for(int msk=0;msk<1<<num;++msk){
		for(int i=1;i<=tot;++i)
			dp[tr[i]][0]=fir[tr[i]][0],dp[tr[i]][1]=fir[tr[i]][1];
		for(int i=0;i<num;++i)
			if(msk>>i&1)dp[U[i]][1]=0,dp[V[i]][0]=0;
			else dp[V[i]][1]=0;
		dfs5(1),fmod(ans+=dp[1][0]),fmod(ans+=dp[1][1]);
	}
	cout<<ans<<'\n';
}