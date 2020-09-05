#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
#define N 409
#define inf (0x3f3f3f3f)
int n,k,a[N],dp[N][N],val[N][N],sum[N];
signed main() {
    n=rd(),k=rd();
    for(int i=1;i<=n;++i)sum[i]=sum[i-1]+(a[i]=rd());
    for(int i=1;i<=n;++i) {
        int mx=0;
        for(int j=i;j<=n;++j)
            mx=max(mx,a[j]),val[i][j]=mx*(j-i+1)-(sum[j]-sum[i-1]);
    }
    for(int i=1;i<=n;++i)dp[0][i]=val[1][i];
    for(int i=1;i<=k;++i) {
        for(int j=1;j<=n;++j) {
            dp[i][j]=inf;
            for(int t=0;t<j;++t)
                dp[i][j]=min(dp[i][j],dp[i-1][t]+val[t+1][j]);
        }
    }
    printf("%d\n",dp[k][n]);
    return 0;
}