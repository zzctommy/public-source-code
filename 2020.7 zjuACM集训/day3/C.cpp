#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=3e5+10;
const int M=35;
int n,m,X,dp[N][M],mx[N][M],a[N],sum[N],ans=-1e16;
signed main() {
	n=rd(),m=rd(),X=rd();
	for(rint i=1;i<=n;++i)a[i]=rd(),sum[i]=sum[i-1]+a[i];
	for(rint i=1;i<=n;++i)dp[i][0]=max(a[i],dp[i-1][0]+a[i]);
	for(rint i=1;i<=n;++i)
		for(rint j=1;j<=m;++j)
			dp[i][j]=-1e16;
	for(rint i=1;i<=n;++i) {
		mx[i][0]=max(mx[i-1][0],max(0ll,dp[i][0])-sum[i]*X);
		for(rint j=1;j<=m;++j) {
			dp[i][j]=max(dp[i-1][j]+a[i],mx[i-1][j-1]+X*sum[i]);
			mx[i][j]=max(max(0ll,dp[i][j])-sum[i]*X,mx[i-1][j]);
		}
	}
	for(rint i=1;i<=n;++i)
		for(rint j=0;j<=m;++j)
			ans=max(ans,dp[i][j]);
	printf("%lld\n",ans);
	return 0;
}
