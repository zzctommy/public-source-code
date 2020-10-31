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
const int mod=1e9+7;
LL n;int k,ans,dp[70],inv[70];
int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
void fmod(int&x){x-=mod,x+=x>>31&mod;}
void solve(int cnt,int zaky){
	memset(dp,0,sizeof(dp));
	dp[cnt]=1;
	for(int i=1;i<=k;++i){
		for(int j=0;j<=cnt;++j){
			dp[j]=1ll*dp[j]*inv[j+1]%mod;
			for(int l=j+1;l<=cnt;++l)fmod(dp[j]+=1ll*inv[l+1]*dp[l]%mod);
		}
	}
	int res=0;
	for(int i=0,j=1;i<=cnt;++i)fmod(res+=1ll*dp[i]*j%mod),j=1ll*j*zaky%mod;
	ans=1ll*ans*res%mod;
}
signed main(){
	std::cin>>n>>k,ans=1,inv[1]=1;
	for(int i=2;i<=69;++i)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(LL i=2;i*i<=n;++i){
		if(n%i==0){
			int cnt=0;
			while(n%i==0)n/=i,++cnt;
			solve(cnt,i%mod);
		}
	}
	if(n>1)solve(1,n%mod);
	std::cout<<ans<<'\n';
}