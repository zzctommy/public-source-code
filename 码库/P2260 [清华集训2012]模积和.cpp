#include<bits/stdc++.h>
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int mod=19940417;
int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
int n,m,ans,inv[7];
int f(int n){
	int res=0;
	for(int l=1,r,t;l<=n;l=r+1)
		r=n/(n/l),t=1ll*(r-l+1)*(l+r)/2%mod,res=(res+1ll*t*(n/l)%mod)%mod;
	return (res+mod)%mod;
}
int h(int n){
	return 1ll*n*(n+1)%mod*(n+n+1)%mod*inv[6]%mod;
}
int g(int n,int m){
	int res=1ll*n*m%mod*n%mod;
	res=(res-1ll*m*f(n)%mod)%mod;
	int tmp=0;
	for(int l=1,r,t;l<=n;l=r+1)
		r=std::min(n,m/(m/l)),t=1ll*(l+r)*(r-l+1)/2%mod,tmp=(tmp+1ll*t*(m/l)%mod)%mod;
	res=(res-1ll*tmp*n%mod)%mod;
	for(int l=1,r;l<=n;l=r+1)
		r=std::min(n/(n/l),m/(m/l)),res=(res+1ll*(h(r)-h(l-1))*(n/l)%mod*(m/l)%mod)%mod;
	return (res+mod)%mod;
}
signed main(){
	inv[1]=1;
	for(int i=2;i<=6;++i)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	n=read(),m=read();
	if(n>m)std::swap(n,m);
	printf("%lld\n",(1ll*(1ll*n*n%mod-f(n)+mod)*(1ll*m*m%mod-f(m)+mod)%mod-g(n,m)+mod)%mod);
}