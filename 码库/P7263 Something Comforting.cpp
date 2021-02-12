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
const int N=1000005;
#define mod 998244353
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
int n,s,fac[N],ifc[N],ans;
char str[N];
inline int comb(int n,int m){return n<m?0:1ll*fac[n]*ifc[m]%mod*ifc[n-m]%mod;}
signed main(){
	scanf("%d%s",&n,str+1);
	for(int i=1,now=0;i<=n<<1;++i){
		str[i]==')'?--now:++now;
		s+=!now;
	}
	fac[0]=1;rep(i,1,n<<1)fac[i]=1ll*fac[i-1]*i%mod;
	ifc[n<<1]=qpow(fac[n<<1],mod-2);per(i,n*2-1,0)ifc[i]=1ll*(i+1)*ifc[i+1]%mod;
	ans=1ll*fac[n<<1]*qpow(comb(2*n-1,n-1),mod-2)%mod;
	ans=1ll*ans*qpow(2,s-1)%mod;
	ans=1ll*ans*qpow(fac[n<<1],mod-2)%mod;
	cout<<ans<<'\n';
}