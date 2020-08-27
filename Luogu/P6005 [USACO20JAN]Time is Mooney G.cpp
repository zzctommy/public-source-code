#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int n,m,c,dp[1409][1009],ans,p[1009];
vector<int>g[1009];
signed main() {
	n=rd(),m=rd(),c=rd();
	for(int i=1;i<=n;++i)p[i]=rd();
	for(int i=1;i<=m;++i){
		int x=rd(),y=rd();
		g[y].pb(x);
	}
	memset(dp,-0x3f,sizeof(dp));
	dp[0][1]=0;
	for(int i=1;i<=1400;++i) {
		for(int u=1;u<=n;++u) {
			for(int v:g[u])dp[i][u]=max(dp[i][u],dp[i-1][v]);
			dp[i][u]+=p[u];
		}
		ans=max(ans,dp[i][1]-i*i*c);
	}
	printf("%d\n",ans);
	return 0;
}
