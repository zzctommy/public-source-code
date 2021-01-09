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
const int N=1000005;
namespace math{
int fac[N],ifc[N];
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
void fmod(int&x){x-=mod,x+=x>>31&mod;}
int comb(int n,int m){return n<m?0:1ll*fac[n]*ifc[m]%mod*ifc[n-m]%mod;}
void initmath(const int&n=N-1){
	fac[0]=1;for(int i=1;i<=n;++i)fac[i]=1ll*i*fac[i-1]%mod;
	ifc[n]=qpow(fac[n],mod-2);for(int i=n-1;i>=0;--i)ifc[i]=1ll*(i+1)*ifc[i+1]%mod;
}
}
using math::qpow;
using math::fmod;
int n,ans;
int f(int x,int y){
	return 1ll*qpow(3,1ll*(n-x)*(n-y)%(mod-1))*((!x||!y)?qpow(3,x+y):3)%mod;
}
signed main(){
	math::initmath();
	n=read();
	for(int i=1;i<=n;++i){
        const int t=qpow(3,n-i);
        int res=3ll*(qpow(t-1,n)-qpow(t,n)+mod)%mod;
        fmod(res+=1ll*qpow(t,n)*qpow(3,i)%mod);
        fmod(ans+=1ll*math::comb(n,i)*(i&1?mod-res:res)%mod);
    }
    for(int i=0;i<=n;++i)fmod(ans+=1ll*math::comb(n,i)*(i&1?mod-f(0,i):f(0,i))%mod);
	fmod(ans=qpow(3,1ll*n*n%(mod-1))-ans+mod);
	cout<<ans<<'\n';
}