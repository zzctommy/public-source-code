#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
#define N 109
int dp[N][N][N],n,a[N],ans[N];//i day;j times;len=k
signed main() {
	n=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	memset(dp,0x3f,sizeof(dp));
	memset(ans,0x3f,sizeof(ans));
	dp[1][1][0]=(a[1]!=0);
	for(int i=2;i<=n;++i) {
		for(int j=1;j<=i;++j) {
			for(int k=1;k<=i;++k)dp[i][j][k]=dp[i-1][j][k-1]+(a[i]!=k);
			for(int k=0;k<=i;++k)dp[i][j][0]=min(dp[i][j][0],dp[i-1][j-1][k]+(a[i]!=0));
		}
	}
	for(int j=1;j<=n;++j)
		for(int k=0;k<=n;++k)
			ans[j]=min(ans[j],dp[n][j][k]);
	for(int i=1;i<=n;++i)printf("%d\n",ans[i]);
	return 0;
}