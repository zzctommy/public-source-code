#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define N 4500
int n,mod,ans,dp[N][N];
signed main(){
	n=read(),mod=read();
	dp[1][1]=1;
	for(int i=2;i<=n;++i){
		for(int j=1;j<=i;++j)
			dp[i][j]=(dp[i][j-1]+dp[i-1][i-j+1])%mod;
	}
	for(int i=1;i<=n;++i)ans=(ans+dp[n][i])%mod;
	printf("%d\n",ans*2%mod);
	return 0;
}