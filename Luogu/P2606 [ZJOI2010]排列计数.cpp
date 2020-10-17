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
	while(!isdigit(ch)) {if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?x:-x;
}
const int N=1000005;
int n,mod;
int siz[N],dp[N],fac[N],ifc[N];
int qpow(int n,int k){
	int res=1;
	for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;
	return res;
}
int C(int n,int m){
	return 1ll*fac[n]*ifc[m]%mod*ifc[n-m]%mod;
}
signed main(){
	n=read(),mod=read(),fac[0]=1;
	for(int i=1;i<=n;++i)siz[i]=dp[i]=1,fac[i]=1ll*fac[i-1]*i%mod;
	ifc[n]=qpow(fac[n],mod-2);for(int i=n-1;i>=0;--i)ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
	for(int i=n;i>=1;--i)siz[i>>1]+=siz[i];
	for(int i=1;i<=n;++i)dp[i]=i<<1<=n?C(siz[i]-1,siz[i<<1]):1;
	for(int i=n;i>=1;--i)dp[i>>1]=1ll*dp[i>>1]*dp[i]%mod;
	printf("%d\n",dp[1]);
	return 0;
}