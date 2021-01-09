#include<bits/stdc++.h>
using namespace std;
#define rint register int
#define int long long
#define N 200010
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
int dp[2][129],n,p,k;
struct node{
	int a,s[8];
}a[N];
inline bool cmp(const node &a,const node &b) {
	return a.a>b.a;
}
signed main() {
	n=rd(),p=rd(),k=rd();
	for(rint i=1;i<=n;++i)a[i].a=rd();
	for(rint i=1;i<=n;++i)
		for(rint j=0;j<p;++j)
			a[i].s[j]=rd();
	sort(a+1,a+n+1,cmp);
	for(rint i=1;i<(1<<p);++i)dp[0][i]=-1;
	for(rint i=1,u=1;i<=n;++i,u^=1) {
		for(rint i=1;i<(1<<p);++i)dp[u][i]=-1;
		for(rint mask=0;mask<(1<<p);++mask) {
			int tmp=0;
			for(rint j=0;j<p;++j)if(mask&(1<<j))++tmp;
			tmp=i-1-tmp;
			if(tmp<k){ if(~dp[u^1][mask])dp[u][mask]=dp[u^1][mask]+a[i].a;}
			else dp[u][mask]=dp[u^1][mask];
			for(rint j=0;j<p;++j)
				if((mask&(1<<j))&&~dp[u^1][mask^(1<<j)])
					dp[u][mask]=max(dp[u][mask],dp[u^1][mask^(1<<j)]+a[i].s[j]);
		}
	}
	printf("%lld\n",dp[n&1][(1<<p)-1]);
	return 0;
}