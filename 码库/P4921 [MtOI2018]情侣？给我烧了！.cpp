//Orz cyn2006
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
#define N 2005
#define mod 998244353
int n,f[N],g[N],fac[N],ifc[N],pw2[N];
int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
void init(){
	int up=2000;
	fac[0]=1,pw2[0]=1;
	for(int i=1;i<=up;++i)fac[i]=1ll*fac[i-1]*i%mod,pw2[i]=(pw2[i-1]<<1)%mod;
	ifc[up]=qpow(fac[up],mod-2);
	for(int i=up-1;i>=0;--i)ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
	up=1000;
	for(int i=0;i<=up;++i){
		for(int j=0;j<=i;++j)
			f[i]=(f[i]+1ll*(j&1?-1:1)*pw2[j]*ifc[j]%mod*fac[2*i-2*j]%mod*ifc[i-j]%mod*ifc[i-j]%mod+mod)%mod;
	}
}
int A(int n,int m){return 1ll*fac[n]*ifc[n-m]%mod;}
int C(int n,int m){return 1ll*fac[n]*ifc[n-m]%mod*ifc[m]%mod;}
signed main(){
	init();
	for(int T=read();T;--T){
		n=read();
		for(int i=0;i<=n;++i)printf("%lld\n",1ll*pw2[i]*fac[n]%mod*fac[n]%mod*ifc[i]%mod*f[n-i]%mod);
	}
}
