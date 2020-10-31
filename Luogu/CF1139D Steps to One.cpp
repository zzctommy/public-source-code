#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define mkp(x,y) make_pair(x,y)
#define fi first
#define se second
#define pb(x) push_back(x)
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define N 100005
#define mod 1000000007
int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*res*n%mod;return res;}
void fmod(int&x){x+=x>>31&mod,x-=mod,x+=x>>31&mod;}
int m,mu[N],pri[N],cnt,f[N],dp[N],inv[N],ans;
bool vis[N];
vector<int>d[N];
void Sieve(const int&K){
	mu[1]=1;
	for(int i=2;i<=K;++i){
		if(!vis[i])mu[i]=-1,pri[++cnt]=i;
		for(int j=1;i*pri[j]<=K;++j){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0){mu[i*pri[j]]=0;break;}
			mu[i*pri[j]]=-mu[i];
		}
	}
	for(int i=1;i<=K;++i)
		for(int j=1;i*j<=K;++j)
			d[i*j].pb(i);
	inv[1]=1;
	for(int i=2;i<=K;++i)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
}
signed main(){
	cin>>m,Sieve(m);
	dp[1]=0;
	for(int i=2;i<=m;++i){
		int res=m;
		for(int j:d[i])
			fmod(res+=1ll*(m/j)*f[j]%mod);
		dp[i]=1ll*res*inv[m-m/i]%mod;
		for(int j=1;i*j<=m;++j)
			fmod(f[i*j]+=dp[i]*mu[j]);
	}
	ans=m;
	for(int i=1;i<=m;++i)fmod(ans+=dp[i]);
	printf("%lld\n",1ll*ans*inv[m]%mod);
	return 0;
}