#include<bits/stdc++.h>
using namespace std;
#define N 3005
#define mod 1000000007
int n,q,x[N],y[N],a[N],dp[N][N],ans;
signed main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	for(int i=1;i<=q;++i)scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			dp[i][j]=a[i]>a[j];
	const int iv2=(mod+1)>>1;
	for(int i=1;i<=q;++i){
		dp[x[i]][y[i]]=dp[y[i]][x[i]]=1ll*iv2*(dp[x[i]][y[i]]+dp[y[i]][x[i]])%mod;
		for(int j=1;j<=n;++j){
			if(j==x[i]||j==y[i])continue;
			dp[x[i]][j]=dp[y[i]][j]=1ll*iv2*(dp[x[i]][j]+dp[y[i]][j])%mod,
			dp[j][x[i]]=dp[j][y[i]]=1ll*iv2*(dp[j][x[i]]+dp[j][y[i]])%mod;
		}
	}
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
			ans=(ans+dp[i][j])%mod;
	for(int i=1;i<=q;++i)ans=(ans<<1)%mod;
	printf("%d\n",ans);
}
