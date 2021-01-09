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
const int N=1000009;
const int inf=0x3f3f3f3f;
int n,dp[N][3],a[N],ans;
signed main() {
	n=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	dp[1][0]=dp[1][1]=dp[1][2]=inf,dp[1][a[1]+1]=0;
	for(int i=2;i<=n;++i) {
		if(a[i]==-1) {
			dp[i][0]=dp[i-1][0];
			if(a[i-1]==1)dp[i][1]=min(dp[i-1][0],dp[i-1][1])+1;
			else dp[i][1]=inf;
			if(a[i-1]==1)dp[i][2]=min(dp[i-1][0],min(dp[i-1][1],dp[i-1][2]))+2;
			else dp[i][2]=dp[i-1][2]+2;
		} else if(a[i]==0) {
			dp[i][0]=dp[i-1][0]+1;
			dp[i][1]=min(dp[i-1][0],dp[i-1][1]);
			if(a[i-1]==1)dp[i][2]=min(dp[i-1][0],min(dp[i-1][1],dp[i-1][2]))+1;
			else dp[i][2]=dp[i-1][2]+1;
		} else {
			dp[i][0]=dp[i-1][0]+2;
			if(a[i-1]==-1)dp[i][1]=min(dp[i-1][0],dp[i-1][1])+1;
			else dp[i][1]=dp[i-1][0]+1;
			dp[i][2]=min(dp[i-1][0],min(dp[i-1][1],dp[i-1][2]));
		}
	}
	ans=min(dp[n][0],min(dp[n][1],dp[n][2]));
	if(ans==inf)puts("BRAK");
	else printf("%d\n",ans);
	return 0;
}
