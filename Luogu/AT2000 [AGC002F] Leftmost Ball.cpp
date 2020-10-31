#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define x first
#define y second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 2505
#define mod 1000000007
int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
int n,k,fac[N*N],ifac[N*N],dp[N][N];
int C(int n,int m){return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;}
void init(const int&lim){
	fac[0]=1;for(int i=1;i<=lim;++i)fac[i]=1ll*fac[i-1]*i%mod;
	ifac[lim]=qpow(fac[lim],mod-2);for(int i=lim-1;i>=0;--i)ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
}
signed main(){
	n=read(),k=read(),init(n*k);
	if(k==1)return puts("1"),0;
	for(int i=1;i<=n;++i)dp[i][0]=1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=i;++j){
			dp[i][j]=(dp[i-1][j]+
			1ll*dp[i][j-1]*(n-j+1)%mod*C(n*k-i-(j-1)*(k-1)-1,k-2)%mod)%mod;
		}
	printf("%d\n",dp[n][n]);
	return 0;
}
/*
dp[sum of white][sum kinds of ball]
*/