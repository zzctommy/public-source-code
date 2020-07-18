#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
#define int long long
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const db eps=1e-7;
db randeps() {
	return (db)rand()/RAND_MAX*eps;
}
const int N=100010;
int n,m,a[N],ans[2][N],sum;
db dp[2][N];
int pre[2][N],tim[2][N];
int check(db x) {
	dp[0][1]=x,dp[1][1]=x>0?x:0,
	pre[0][1]=0,pre[1][1]=x>0,
	tim[0][1]=1,tim[1][1]=x>0;
	for(rint i=2;i<=n;++i) {
		dp[0][i]=dp[0][i-1]+a[i]+randeps(),tim[0][i]=tim[0][i-1],pre[0][i]=i;
		if(dp[1][i-1]+x>dp[0][i])dp[0][i]=dp[1][i-1]+x+randeps(),tim[0][i]=tim[1][i-1]+1,pre[0][i]=pre[1][i-1];
		dp[1][i]=dp[1][i-1],pre[1][i]=pre[1][i-1],tim[1][i]=tim[1][i-1];
		if(dp[1][i]<dp[0][i])dp[1][i]=dp[0][i],pre[1][i]=i,tim[1][i]=tim[0][i];
	}
	return tim[1][n];
}
signed main() {
	srand(time(0));
	n=rd(),m=rd();
	for(rint i=2;i<=n;++i)a[i]=rd();
	db l=-1e7,r=1e7;
	while("fyy AK IOI") {
		db mid=(l+r)/2;int k=check(mid);
		if(k==m) {
			int tot=0,i=pre[1][n],j;
			while(i) {
				j=i;
				for(;j>0;--j)
					if(pre[0][j]==j)sum+=a[j];
					else break;
				ans[0][++tot]=j,ans[1][tot]=i;
				i=pre[0][j];
			}
			printf("%lld\n",sum);
			for(rint i=1;i<=tot;++i)printf("%lld %lld\n",ans[0][i],ans[1][i]);
			return 0;
		}
		if(k<m)l=mid;
		else r=mid;
	} 
}
