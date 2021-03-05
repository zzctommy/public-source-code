#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=1000005;
#define mod 1000000007
inline int qpow(int n,int k){
	int res=1;
	for(;k;k>>=1,n=1ll*n*n%mod)
		if(k&1)res=1ll*n*res%mod;
	return res;
}
int fac[N],ifc[N];
inline void init(const int&n=N-1){
	fac[0]=1;for(int i=1;i<=n;++i)fac[i]=1ll*fac[i-1]*i%mod;
	ifc[n]=qpow(fac[n],mod-2);for(int i=n-1;i>=0;--i)ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
}
inline int C(int n,int m){return n<m?0:1ll*fac[n]*ifc[m]%mod*ifc[n-m]%mod;}
int n,k,ans;
void Main(){
	n=read(),k=read();
	int a0=n,a1=0,b0=1,b1=0;
	rep(i,1,k){
		int c0=0,c1=0,d0=0,d1=0;
		if(a0==1){
			if(b1){
				if(a1&1)b0+=b1;
				else b1*=2;
				a1>>=1;
			}
			break;
		}
		if(!b1){
			if(a0&1)c0=a0>>1,c1=c0+1,d0=b0,d1=b0;
			else c0=a0>>1,d0=b0*2;
		}else{
			c0=a0>>1,c1=c0+1;
			if(a0&1)d0+=b0,d1+=b0;
			else d0+=b0*2;
			if(a1&1)d0+=b1,d1+=b1;
			else d1+=b1*2;
		}
		a0=c0,a1=c1,b0=d0,b1=d1;
	}
	ans=1ll*fac[n]*qpow(ifc[a0],b0)%mod*qpow(ifc[a1],b1)%mod;
	printf("%d\n",ans);
}
signed main(){
	init();
	for(int T=read();T;--T)Main();
}