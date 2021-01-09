#include<bits/stdc++.h>
using namespace std;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
typedef long long LL;
const int N=100009;
int n,m,ans;
int scc[N],dfn[N],low[N],timer,stk[N],top,COL,siz[N],ind[N];
vector<int>g[N];
void tarjan(int u) {
	stk[++top]=u,dfn[u]=low[u]=++timer;
	for(int v:g[u])
		if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
		else if(!scc[v])low[u]=min(low[u],dfn[v]);
	if(low[u]==dfn[u]) {
		++COL;
		while(stk[top+1]!=u)scc[stk[top--]]=COL,++siz[COL];
	}
}
signed main(){
	n=rd(),m=rd();
	for(int i=1;i<=m;++i) {
		int x=rd(),y=rd();g[y].push_back(x);
	}
	for(int i=1;i<=n;++i)if(!dfn[i])tarjan(i);
	for(int u=1;u<=n;++u)
		for(int v:g[u])if(scc[u]!=scc[v])++ind[scc[v]];
	for(int i=1,k=0;i<=COL;++i)if(!ind[i]){
		++k;if(k>1)return puts("0"),0;
		ans+=siz[i];
	}
	printf("%d\n",ans);
	return 0;
}