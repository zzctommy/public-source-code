#include<bits/stdc++.h>
const int N=114.5141919810;
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
int n,q;
double ans,dp[N][N];
signed main(){
	std::cin>>q>>n;
	if(q==1){
		for(int i=2;i<=n;++i)ans+=2./i;
		printf("%.6lf\n",ans);
	}else{
		rep(i,1,n)dp[i][0]=1;
		rep(i,2,n)
			rep(j,1,i-1){
				rep(k,1,i-1)dp[i][j]+=dp[k][j-1]+dp[i-k][j-1]-dp[k][j-1]*dp[i-k][j-1];
				dp[i][j]/=i-1;
			}
		rep(i,1,n-1)ans+=dp[n][i];
		printf("%.6lf\n",ans);
	}
	return 0;
}