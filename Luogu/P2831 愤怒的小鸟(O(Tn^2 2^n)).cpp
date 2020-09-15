#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
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
const int N=18;
const int M=(1<<N)+5;
int n,dp[M],inc[N][N];
double x[N],y[N],eps=1e-9;
int calc(int i,int j) {
	double div=x[j]/x[i];
	double a=(y[j]-y[i]*div)/(x[j]*x[j]-x[i]*x[i]*div);
	double b=(y[i]-a*x[i]*x[i])/x[i];
	if(a>-eps)return 0;
	int res=0;
	for(int i=0;i<n;++i)if(fabs(a*x[i]*x[i]+b*x[i]-y[i])<eps)res|=1<<i;
	return res;
}
void Main() {
	n=rd(),rd();
	memset(dp,0x3f,sizeof(dp));
	for(int i=0;i<n;++i)scanf("%lf%lf",&x[i],&y[i]);
	for(int i=0;i<n;++i)
		for(int j=i+1;j<n;++j)
			inc[i][j]=calc(i,j);
	dp[0]=0;
	for(int msk=0,t;msk<1<<n;++msk) {
		for(int i=0;i<n;++i) {
			if(msk>>i&1)continue;
			dp[msk|(1<<i)]=min(dp[msk|(1<<i)],dp[msk]+1);
			for(int j=i+1;j<n;++j) {
				if(msk>>j&1)continue;
				dp[msk|inc[i][j]]=min(dp[msk|inc[i][j]],dp[msk]+1);
			}
		}
	}
	printf("%d\n",dp[(1<<n)-1]);
}
signed main() {
	for(int T=rd();T;--T)Main();
}
