#include<bits/stdc++.h>
using namespace std;
int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
#define N 1000009
int n,k,ans=1,mxd[N];
vector<int>g[N];
void dfs(int u,int ft) {
	if(g[u].size()==1)return mxd[u]=0,void();
	vector<int>a;
	for(int v:g[u])if(v!=ft)dfs(v,u),a.push_back(mxd[v]+1);
	sort(a.begin(),a.end());
	while(a.size()>1) {
		if(a[a.size()-1]+a[a.size()-2]<=k)break;
		++ans,a.pop_back();
	}
	mxd[u]=a.back();
}
signed main() {
	n=rd(),k=rd();
	for(int i=1;i<n;++i) {
		int x=rd(),y=rd();
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for(int i=1;i<=n;++i)
		if(g[i].size()>1){dfs(i,0),printf("%d\n",ans);return 0;}
} 