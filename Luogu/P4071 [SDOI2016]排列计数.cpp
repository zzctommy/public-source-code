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
const int mod=1e9+7;
int f[N],fac[N],ifc[N];
int qpow(int n,int k){
	int res=1;
	for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;
	return res;
}
void init(const int&N){
	fac[0]=1;
	for(int i=1;i<=N;++i)fac[i]=1ll*i*fac[i-1]%mod;
	ifc[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=0;--i)ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
	f[0]=1,f[1]=0,f[2]=1;
	for(int i=3;i<=N;++i)f[i]=1ll*(i-1)*(f[i-1]+f[i-2])%mod;
}
int C(int n,int m){
	return 1ll*fac[n]*ifc[m]%mod*ifc[n-m]%mod;
}
signed main(){
	init(N-5);
	for(int T=read();T;--T){
		int n=read(),m=read();
		if(n<m)puts("0");
		else printf("%lld\n",1ll*C(n,m)*f[n-m]%mod);
	}
	return 0;
}