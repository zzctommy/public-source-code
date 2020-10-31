#include<bits/stdc++.h>
typedef long long LL;
typedef double db;
#define x first
#define y second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
const int N=100005;
int n,rt,k[N];
LL ans,dp[N];
std::vector<int>e[N];
int dfs(int u,int ft){
	LL lef=0;
	std::vector<LL>v;
	for(int t:e[u])if(t!=ft)
		lef+=dfs(t,u),v.pb(dp[t]);
	std::sort(v.begin(),v.end()),std::reverse(v.begin(),v.end());
	if(u!=rt)--k[u];
	for(LL i:v)if(k[u])--k[u],dp[u]+=i+2;else break;
	dp[u]+=std::min((LL)k[u],lef)*2,k[u]-=std::min((LL)k[u],lef);
	return k[u];
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i)k[i]=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		e[x].pb(y),e[y].pb(x);
	}
	dfs(rt=read(),0);
	printf("%lld\n",dp[rt]);
	return 0;
}