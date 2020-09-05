#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(a) push_back(a)
#define mkp(a,y) make_pair(a,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int a=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))a=a*10+(ch^48),ch=getchar();
    return a*f;
}
#define N 100009
#define M 29
#define inf (0x3f3f3f3f)
int n,m,k,sum[N][M],dp[N],a[N],dis[M][M],f[M];
char s[N];
signed main() {
	n=rd(),m=rd(),k=rd(),scanf("%s",s+1);
	for(int i=1;i<=n;++i)a[i]=s[i]-'a'+1;
	for(int i=1;i<=m;++i)
		for(int j=1;j<=m;++j)
			dis[i][j]=rd();
	for(int k=1;k<=m;++k)
		for(int i=1;i<=m;++i)
			for(int j=1;j<=m;++j)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			sum[i][j]=sum[i-1][j]+dis[a[i]][j];
	for(int i=1;i<=n;++i) {
		dp[i]=inf;
		if(i>=k*2) {
			for(int j=1;j<=m;++j)
				f[j]=min(f[j],dp[i-k]-sum[i-k][j]);
		}
		for(int j=1;j<=m;++j)
			dp[i]=min(dp[i],f[j]+sum[i][j]);
	}
	printf("%d\n",dp[n]);
	return 0;
}