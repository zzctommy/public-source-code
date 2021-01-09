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
#define mod 998244353
#define N 5000005
int T,n,k;
int pw2[N],fac[N],ifc[N],f[N];
int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
void init(){
	int up=N-5;
	pw2[0]=fac[0]=1;
	for(int i=1;i<=up;++i)fac[i]=1ll*fac[i-1]*i%mod,pw2[i]=(pw2[i-1]<<1)%mod;
	ifc[up]=qpow(fac[up],mod-2);
	for(int i=up-1;i>=0;--i)ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
	f[0]=1,f[1]=0;
	for(int i=2;i<=up;++i)f[i]=4ll*i*(i-1)%mod*(2ll*(i-1)*f[i-2]%mod+f[i-1])%mod;
}
int A(int n,int m){return 1ll*fac[n]*ifc[n-m]%mod;}
int C(int n,int m){return 1ll*fac[n]*ifc[n-m]%mod*ifc[m]%mod;}
signed main(){
	init();
	for(int T=read();T;--T)
		n=read(),k=read(),printf("%lld\n",1ll*A(n,k)*C(n,k)%mod*pw2[k]%mod*f[n-k]%mod);
}
