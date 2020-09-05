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
LL dist[N];
int n,a[N],dif[N],fa[19][N],ans[N];
vector<pair<int,int> >g[N];
void dfs(int u) {
	for(rint i=0;i<g[u].size();++i) {
		int v=g[u][i].first;
		dist[v]=dist[u]+g[u][i].second;
		dfs(v);
	}
}
void solve(int u) {
	for(rint i=0;i<g[u].size();++i) {
		int v=g[u][i].first;
		solve(v);
	}
	int w=u;
	for(rint j=18;j>=0;--j)
		if(fa[j][w]&&dist[u]-dist[fa[j][w]]<=a[u])w=fa[j][w];
	--dif[fa[0][w]],++dif[fa[0][u]];
}
void calc(int u) {
	for(rint i=0;i<g[u].size();++i) {
		int v=g[u][i].first;
		calc(v);
		dif[u]+=dif[v];
	}
}
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i)a[i]=rd();
	for(rint i=2,x,y;i<=n;++i) {
		x=rd(),y=rd();
		fa[0][i]=x;
		g[x].push_back(make_pair(i,y));
	}
	g[0].push_back(make_pair(1,0));
	for(rint i=1;i<=18;++i)
		for(rint j=1;j<=n;++j)
			fa[i][j]=fa[i-1][fa[i-1][j]];
	dfs(1);solve(1);calc(1);
	for(rint i=1;i<=n;++i)printf("%d%c",dif[i]," \n"[i==n]);
	return 0;
}