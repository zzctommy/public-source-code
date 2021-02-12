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
const int N=200005;
#define mod 1000000007
inline int qpow(int n,int k){if(k<0)return 0;int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
int n,k,sum,fac[N],ifc[N],ans;
int comb(int n,int m){return n<m?0:1ll*fac[n]*ifc[m]%mod*ifc[n-m]%mod;}
signed main(){
	n=read(),k=read()-1;
	rep(i,1,n)sum=(sum+read())%mod;
	fac[0]=1;rep(i,1,k)fac[i]=1ll*i*fac[i-1]%mod;
	ifc[k]=qpow(fac[k],mod-2);per(i,k-1,0)ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
	for(int i=0;i<=k;++i){
		int tmp=1ll*comb(k,i)*(qpow(1+i,n-1)+1ll*(n-1)*qpow(1+i,n-2)%mod)%mod;
		(k-i)&1?ans=(ans+mod-tmp)%mod:ans=(ans+tmp)%mod;
	}
	ans=1ll*ans*ifc[k]%mod*sum%mod;
	cout<<ans<<'\n';
}