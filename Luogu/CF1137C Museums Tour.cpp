#include<bits/stdc++.h>
using namespace std;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
inline int rdc() {
	char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	return ch-'0';
}
typedef long long LL;
const int L=100005;
const int M=55;
const int N=L*M;
int n,m,d,k;
LL msk[L];
int dp[N],vis[N];
int scc[N],dfn[N],low[N],timer,stk[N],top,COL,siz[N];
vector<int>g[N],e[N];
int id(int x,int y){return (x-1)*d+y+1;}
inline void tarjan(int u) {
	stk[++top]=u,dfn[u]=low[u]=++timer;
	for(int v:g[u])
		if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
		else if(!scc[v])low[u]=min(low[u],dfn[v]);
	if(low[u]==dfn[u]) {
		++COL;
		while(stk[top+1]!=u)scc[stk[top--]]=COL;
	}
}
inline void dfs(int u) {
	if(dp[u])return;
	for(int v:e[u])dfs(v),dp[u]=max(dp[u],dp[v]);
	dp[u]+=siz[u];
}
signed main(){
	n=rd(),m=rd(),d=rd(),k=n*d;
	for(int i=1;i<=m;++i) {
		int x=rd(),y=rd();
		for(int j=0;j<d;++j)g[id(x,j)].push_back(id(y,(j+1)%d));
	}
	for(int i=1;i<=n;++i)
		for(int j=0;j<d;++j)rdc()&&(msk[i]|=1ll<<j);
	for(int i=1;i<=k;++i)if(!dfn[i])tarjan(i);
	for(int i=1;i<=n;++i) {
		for(int j=0;j<d;++j) {
			int u=id(i,j);
			if(msk[i]>>j&1&&vis[scc[u]]!=i)vis[scc[u]]=i,++siz[scc[u]];
			for(int v:g[u])if(scc[u]!=scc[v])e[scc[u]].push_back(scc[v]);
		}
	}
	dfs(scc[id(1,0)]),printf("%d\n",dp[scc[id(1,0)]]);
	return 0;
}