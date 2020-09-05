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
int n,m,d,ans,dis[N],ds[N],dt[N],s,t;
bool bo[N];
vector<int>g[N];
void dfs1(int u,int ft,int &pos) {
	if(bo[u]&&dis[u]>dis[pos])pos=u;
	for(rint i=0;i<g[u].size();++i) {
		int v=g[u][i];
		if(v==ft)continue;
		dis[v]=dis[u]+1;
		dfs1(v,u,pos);
	}
}
void dfs2(int u,int ft,int *dep) {
	for(rint i=0;i<g[u].size();++i) {
		int v=g[u][i];
		if(v==ft)continue;
		dep[v]=dep[u]+1;
		dfs2(v,u,dep);
	}
}
signed main() {
	n=rd(),m=rd(),d=rd();
	for(rint i=1;i<=m;++i)bo[rd()]=1;
	for(rint i=1,x,y;i<n;++i) {
		x=rd(),y=rd();
		g[x].push_back(y);
		g[y].push_back(x);
	}
	memset(dis,0,sizeof(dis));dfs1(1,0,s);
	memset(dis,0,sizeof(dis));dfs1(s,0,t);
	dfs2(s,0,ds),dfs2(t,0,dt);
	for(rint i=1;i<=n;++i)
		if(ds[i]<=d&&dt[i]<=d)++ans;
	printf("%d\n",ans);
	return 0;
}