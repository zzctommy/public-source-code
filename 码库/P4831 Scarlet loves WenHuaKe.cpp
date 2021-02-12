#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
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

#define mod 998244353
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}
const int N=200005;
int fac[N],ifc[N],ans,n,m,pw2[N],ip2[N];
void initmath(const int&n=N-1){
	fac[0]=1;rep(i,1,n)fac[i]=1ll*i*fac[i-1]%mod;
	ifc[n]=qpow(fac[n],mod-2);per(i,n-1,0)ifc[i]=1ll*(i+1)*ifc[i+1]%mod;
	pw2[0]=1;rep(i,1,n)fmod(pw2[i]=pw2[i-1]<<1);
	const int iv2=(mod+1)>>1;
	ip2[0]=1;rep(i,1,n)ip2[i]=1ll*ip2[i-1]*iv2%mod;
}
int comb(int n,int m){return n<m?0:1ll*fac[n]*ifc[m]%mod*ifc[n-m]%mod;}
int g(int n,int m){
	int res=0;
	rep(i,0,min(n,m-n))fmod(res+=1ll*comb(m,n-i)*comb(m-n+i,i*2)%mod*ip2[n-i]%mod);
	res=1ll*res*fac[n*2]%mod;
	return res;
}
signed main(){
	n=read(),m=read(),initmath();
	for(int i=0;i<=n;++i){
		int res=1ll*comb(n,i)*comb(m,i)%mod*fac[i]%mod*g(n-i,m-i)%mod;
		fmod(ans+=i&1?mod-res:res);
	}
	ans=1ll*ans*qpow(pw2[n],mod-2)%mod;
	printf("%d\n",ans);
}