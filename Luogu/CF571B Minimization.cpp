#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3e5+10;
int n,k,a[N];
ll dp[5005][5005];
int main() {
	memset(dp,0x3f,sizeof(dp));
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i) 
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	int l1=n/k+1,l2=n/k,t1=n%k,t2=k-n%k;
	for(int i=0;i<=t1;++i) {
		for(int j=0;j<=t2;++j) {
			if(!i&&!j) {
				dp[i][j]=0;
				continue;
			}
			if(i)dp[i][j]=min(dp[i][j],dp[i-1][j]-a[l1*(i-1)+l2*j+1]+a[l1*i+l2*j]);
			if(j)dp[i][j]=min(dp[i][j],dp[i][j-1]-a[l1*i+l2*(j-1)+1]+a[l1*i+l2*j]);
		}
	}
	printf("%lld\n",dp[t1][t2]);
	return 0;
}