#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1000000007;
const int N=5005;
int dp[N][N],n,k,ans,m=2;
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
	scanf("%lld%lld",&n,&k);
	dp[0][0]=1;
	for(int i=1;i<=k;++i)
		for(int j=1;j<=i;++j) 
			dp[i][j]=(dp[i-1][j]*j+dp[i-1][j-1]*(n-j+1))%mod;
	for(int i=0;i<=k;++i)
		ans=(ans+1ll*dp[k][i]*qpow(qpow(2,mod-2),i))%mod;
	ans=1ll*ans*qpow(2,n)%mod;
	printf("%lld\n",ans);
	return 0;
}