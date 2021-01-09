#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define mod 1000000007
#define N 405
int n,dp[N][N];
void fmod(int&x){x-=mod,x+=x>>31&mod;}
signed main(){
	n=read();
	for(int i=1;i<=n;++i)dp[i][0]=1;
	dp[1][1]=1;
	for(int i=2;i<=n;++i){
		for(int j=1;j<=n;++j){
			for(int k=0;k<=j-1;++k)fmod(dp[i][j]+=1ll*dp[i-1][k]*dp[i-1][j-1-k]%mod);
			for(int k=0;k<=j;++k)  fmod(dp[i][j]+=1ll*dp[i-1][k]*dp[i-1][j-k]%mod);
			for(int k=0;k<=j;++k)  fmod(dp[i][j]+=1ll*dp[i-1][k]*dp[i-1][j-k]%mod*2*j%mod);
			for(int k=0;k<=j+1;++k)fmod(dp[i][j]+=1ll*dp[i-1][k]*dp[i-1][j+1-k]%mod*j*(j+1)%mod);
		}
	}
	printf("%d\n",dp[n][1]);
	return 0;
}
