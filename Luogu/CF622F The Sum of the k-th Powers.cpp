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
const int N=1000005;
const int mod=1e9+7;
int n,k,ans;
int pri[N/9],cnt,s[N],inv[N],fac[N],ifc[N];
bool vis[N];
int pre[N],suf[N];
int qpow(int n,int k){
	int res=1;
	for(;k;k>>=1,n=1ll*n*n%mod)
		if(k&1)res=1ll*n*res%mod;
	return res;
}
void fmod(int&x){
	x+=x>>31&mod,x-=mod,x+=x>>31&mod;
}
void Sieve(const int&N){
	s[1]=1;
	for(int i=2;i<=N;++i){
		if(!vis[i])pri[++cnt]=i,s[i]=qpow(i,k);
		for(int j=1;j<=cnt&&i*pri[j]<=N;++j){
			vis[i*pri[j]]=1;s[i*pri[j]]=1ll*s[i]*s[pri[j]]%mod;
			if(i%pri[j]==0)break;
		}
	}
	for(int i=1;i<=N;++i)fmod(s[i]+=s[i-1]);
	inv[1]=1;for(int i=2;i<=N;++i)inv[i]=1ll*inv[mod%i]*(mod-i)%mod;
	fac[0]=1;for(int i=1;i<=N;++i)fac[i]=1ll*i*fac[i-1]%mod;
	ifc[N]=qpow(fac[N],mod-2);for(int i=N-1;i>=0;--i)ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
	pre[0]=1;for(int i=1;i<=N;++i)pre[i]=1ll*pre[i-1]*(n-i)%mod;
	suf[N+1]=1;for(int i=N;i>0;--i)suf[i]=1ll*suf[i+1]*(n-i)%mod;
}
void lagrange(){
	for(int i=1;i<=k+2;++i){
		int A=1ll*pre[i-1]*suf[i+1]%mod;
		int B=1ll*ifc[i-1]*((k+2-i)&1?-1:1)*ifc[k+2-i]%mod;
		ans=(ans+1ll*s[i]*A%mod*B%mod)%mod;
	}
}
signed main(){
	cin>>n>>k,Sieve(k+2);
	if(n<=k+2)return cout<<s[n]<<'\n',0;
	lagrange(),fmod(ans),cout<<ans<<'\n';
	return 0;
}