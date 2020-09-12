#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
const int N=5005;
int dp[N][N],n,m,k,ans,c=1,p;
int qpow(int n,int k) {
	int res=1;
	while(k) {
		if(k&1)res=res*n%mod;
		n=n*n%mod;
		k>>=1;
	}
	return res;
}
signed main() {
	scanf("%lld%lld%lld",&n,&m,&k);
	dp[0][0]=1;
	for(int i=1;i<=k;++i)
		for(int j=1;j<=i;++j) 
			dp[i][j]=(dp[i-1][j]*j+dp[i-1][j-1]*(n-j+1))%mod;
	p=qpow(m,mod-2);
	for(int i=0;i<=k;++i)
		ans=(ans+dp[k][i]*c)%mod,c=c*p%mod;
	printf("%lld\n",ans);
	return 0;
}