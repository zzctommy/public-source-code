#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
#define int long long
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=1e6+10;
int n,p1,p2,p3;
int t[N],s[N],dp[N][3];
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i)s[i]=rd();
	for(rint i=1;i<=n;++i)t[i]=rd();
	p1=rd(),p2=rd(),p3=rd();
	dp[1][0]=dp[1][1]=s[1];
	for(rint i=2;i<=n;++i) {
		dp[i][0]=max(dp[i-1][1]+s[i]/100*(t[i-1]<t[i]?p1:100),dp[i-1][2]+s[i]);
		dp[i][1]=max(max(dp[i-1][1]+s[i]/100*p3,dp[i-1][0]+s[i]/100*(t[i-1]>t[i]?p2:100)),dp[i-1][2]+s[i]);
		dp[i][2]=max(dp[i-1][0],dp[i-1][1]);
	}
	printf("%lld\n",max(max(dp[n][0],dp[n][1]),dp[n][2]));
	return 0;
}
