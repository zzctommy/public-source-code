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
const int N=300010;
vector<int>g[N];
int n,q,ans[N],siz[N],root,mx[N],sum,fa[N];
void dfs(int u) {
	siz[u]=1;
	for(rint i=0;i<g[u].size();++i) {
		int v=g[u][i];
		dfs(v),siz[u]+=siz[v],mx[u]=max(mx[u],siz[v]);
	}
	int mxu=mx[u],rt=u;
	for(rint i=0;i<g[u].size();++i) {
		int v=g[u][i],w=ans[v],now=max(mx[w],siz[u]-siz[w]),it=w;
		while(fa[w]!=u) {
			w=fa[w];
			int tmp=max(mx[w],siz[u]-siz[w]);
			if(tmp<now)now=tmp,it=w;
			else break;
		}
		if(now<mxu)mxu=now,rt=it;
	}
	ans[u]=rt;
} 
signed main() {
	n=rd(),q=rd();
	for(rint i=2,x;i<=n;++i)x=rd(),g[x].push_back(i),fa[i]=x;
	mx[0]=n;dfs(1);
	while(q--)printf("%d\n",ans[rd()]);
	return 0;
}