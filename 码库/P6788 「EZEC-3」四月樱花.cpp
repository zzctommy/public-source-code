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
typedef unsigned int uint;
uint t,mod,ans=1;
inline uint qpow(uint n,uint k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
uint f(uint n){
	uint res=0;
	for(uint l=1,r;l<=n;l=r+1)
		r=n/(n/l),(res+=1ll*(n/l)*(r-l+1))%=mod-1;
	return res;
}
signed main(){
	cin>>t>>mod;
	for(uint l=1,r;l<=t;l=r+1)
		r=t/(t/l),ans=1ll*ans*qpow(1ll*l*qpow(r+1,mod-2)%mod,f(t/l))%mod;
	ans=1ll*ans*ans%mod;
	cout<<ans<<'\n';
	return 0;
}