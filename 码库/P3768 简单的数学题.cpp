#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int mod,ans,inv6,inv2;
LL n;
const int N=8000005;
const int C=N-5;
inline int qpow(int n,int k){
	int res=1;
	while(k){
		if(k&1)res=1ll*res*n%mod;
		n=1ll*n*n%mod,k>>=1; 
	}
	return res;
}
int pri[N],cnt,phi[N],sum[N];
bool vis[N];
void Sieve(const int&N){
	phi[1]=1;
	for(int i=2;i<=N;++i){
		if(!vis[i])pri[++cnt]=i,phi[i]=i-1;
		for(int j=1;j<=cnt&&i*pri[j]<=N;++j){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0){phi[i*pri[j]]=1ll*phi[i]*pri[j]%mod;break;}
			else phi[i*pri[j]]=1ll*phi[i]*phi[pri[j]]%mod;
		}
	}
	for(int i=1;i<=N;++i)sum[i]=(1ll*i*i%mod*phi[i]%mod+sum[i-1])%mod;
}
int f1(LL x){//一次方和 
	return x%=mod,1ll*x*(x+1)%mod*inv2%mod; 
}
int f2(LL x){//二次方和 
	x%=mod;
	LL res=1ll*x*(x+1)%mod*(2*x+1)%mod*inv6%mod;
	return res;
}
int f3(LL x){//三次方和 
	int t=f1(x%mod);
	return 1ll*t*t%mod;
}
unordered_map<LL,int>mp;
int djs(LL x){
	if(x<=C)return sum[x];
	if(mp[x])return mp[x];
	int res=f3(x);
	for(LL l=2,r;l<=x;l=r+1)
		r=x/(x/l),res=(res-1ll*(f2(r)-f2(l-1))*djs(x/l)%mod)%mod;
	return mp[x]=(res+mod)%mod;
}
signed main(){
	scanf("%d%lld",&mod,&n),Sieve(min(n,1ll*C));
	inv6=qpow(6,mod-2),inv2=qpow(2,mod-2);
	for(LL l=1,r;l<=n;l=r+1){
		r=n/(n/l),ans=(ans+1ll*(djs(r)-djs(l-1))*f3(n/l)%mod)%mod;
	} 
	printf("%d\n",(ans+mod)%mod);
	return 0;
}