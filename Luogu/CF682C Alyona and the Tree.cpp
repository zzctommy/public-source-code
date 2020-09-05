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
const int N=100010;
int n,a[N],siz[N],ans;
vector<pair<int,int> >g[N];
void dfs1(int u) {
	siz[u]=1;
	for(rint i=0;i<g[u].size();++i) {
		dfs1(g[u][i].first);
		siz[u]+=siz[g[u][i].first];
	}
}
void dfs2(int u,LL sum) {
	if(a[u]<sum) {ans+=siz[u];return;}
	for(rint i=0;i<g[u].size();++i)
		dfs2(g[u][i].first,max((LL)g[u][i].second,sum+g[u][i].second));
}
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i)a[i]=rd();
	for(rint i=2,x,y;i<=n;++i) {
		x=rd(),y=rd();
		g[x].push_back(make_pair(i,y));
	}
	dfs1(1),dfs2(1,0);
	printf("%d\n",ans);
	return 0;
}