#include<bits/stdc++.h>
using namespace std;
#define rint register int
typedef long long LL;
const int inf=1000000007;
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
const int N=200010;
vector<int>g[N];
int n,deg[N],ans,col[N];
void dfs(int u,int ft) {
	int tmp=0;
	for(rint i=0;i<g[u].size();++i) {
		int v=g[u][i];
		if(v==ft)continue;
		++tmp;
		while(tmp==col[ft]||tmp==col[u])++tmp;
		col[v]=tmp;
		dfs(v,u);
	}
}
signed main() {
	n=rd();
	for(rint i=1,x,y;i<n;++i) {
		x=rd(),y=rd();
		g[x].push_back(y);
		g[y].push_back(x);
		++deg[y],++deg[x];
	}
	for(rint i=1;i<=n;++i)ans=max(ans,deg[i]);
	col[1]=1;dfs(1,0);
	printf("%d\n",ans+1);
	for(rint i=1;i<=n;++i)printf("%d ",col[i]);
	return 0;
}