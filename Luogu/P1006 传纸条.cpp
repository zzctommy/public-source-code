#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define fyy_AK_IOI return 0
#define rint register int
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=60;
int dp[N*2][N][N],n,m,a[N<<1][N];
signed main() {
	m=rd(),n=rd();
	for(rint i=1;i<=m;++i)
		for(rint j=1;j<=n;++j)
			a[i][j]=rd();
	memset(dp,-1,sizeof(dp));
	dp[2][1][1]=0;
	for(rint i=3;i<=m+n-1;++i) {
		for(rint j=1;j<=n;++j) {
			for(rint k=j+1;k<=n;++k) {
				int tmp=-1;
                tmp=max(dp[i-1][j-1][k-1],max(dp[i-1][j-1][k],max(dp[i-1][j][k-1],dp[i-1][j][k])));
				if(tmp!=-1)dp[i][j][k]=tmp+a[i-j][j]+a[i-k][k];
			}
		} 
	}
	printf("%d\n",dp[n+m-1][n-1][n]);
	return 0;
}