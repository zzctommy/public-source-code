#include<bits/stdc++.h>
using namespace std;
#define rint register int
#define inf 100000000
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
#define N (2010)
int n,h,l,r,dp[N][N],ans,a[N];
int main() {
	memset(dp,-0x3f,sizeof(dp));dp[0][0]=0;
	n=rd(),h=rd(),l=rd(),r=rd();
	for(rint i=1;i<=n;++i)a[i]=rd();
	for(rint i=1;i<=n;++i) 
		for(rint j=0;j<h;++j)
			dp[i][j]=max(dp[i-1][((j-a[i])%h+h)%h]+(l<=j&&j<=r),dp[i-1][((j-a[i]+1)%h+h)%h]+(l<=j&&j<=r));
	for(rint i=0;i<h;++i)ans=max(ans,dp[n][i]);
	printf("%d\n",ans);
	return 0;
}