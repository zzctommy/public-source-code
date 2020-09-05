#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(a) push_back(a)
#define mkp(a,y) make_pair(a,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int a=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))a=a*10+(ch^48),ch=getchar();
    return a*f;
}
#define N 100009
#define zky 1000000007
int n,q,num[N],tr[N],a[N],dp[N],ans;
int fa[N],top[N],dep[N],son[N],dfn[N],siz[N],timer;
vector<int>g[N];
void add(int x,int d) {
	for(int i=x;i<=n;i+=i&-i)tr[i]+=d;
}
int ask(int x) {
	int res=0;
	for(int i=x;i>0;i-=i&-i)(res+=tr[i])%=zky;
	return res;
}
void dfs1(int u,int ft) {
	siz[u]=1;
	for(int v:g[u]) {
		if(v==ft)continue;
		dep[v]=dep[u]+1,fa[v]=u;
		dfs1(v,u),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp) {
	dfn[u]=++timer,top[u]=tp;
	if(son[u])dfs2(son[u],tp);
	for(int v:g[u]) {
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
int query(int x,int y) {
	int res=0;
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
		res+=ask(dfn[x])-ask(dfn[top[x]]-1);
		x=fa[top[x]];
	}
	if(dfn[x]>dfn[y])x^=y^=x^=y;
	res+=ask(dfn[y])-ask(dfn[x]-1);
	return res;
}
signed main() {
	n=rd(),q=rd();
	for(int i=1;i<n;++i) {
		int x=rd(),y=rd();
		g[x].pb(y),g[y].pb(x);
	}
	dfs1(1,0),dfs2(1,1);
	while(q--) {
		int k=rd(),m=rd(),r=rd();
		for(int i=1;i<=k;++i)a[i]=rd(),add(dfn[a[i]],1);
		for(int i=1;i<=k;++i)num[i]=query(r,a[i])-1,dp[i]=0;
		dp[0]=1,ans=0;
		sort(num+1,num+k+1);
		for(int i=1;i<=k;++i) {
			for(int j=min(m,i);j>=0;--j) {
				if(j<=num[i])dp[j]=0;
				if(!j)break;
				dp[j]=(dp[j-1]+1ll*dp[j]*(j-num[i])%zky)%zky;
				//dp[i][j]=dp[i-1][j-1]+dp[i-1][j]*(j-num[i])
			}
		}
		for(int i=1;i<=k;++i)ans=(ans+dp[i])%zky;
		printf("%d\n",ans);
		for(int i=1;i<=k;++i)add(dfn[a[i]],-1);
	}
	return 0;
}