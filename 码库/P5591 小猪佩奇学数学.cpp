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
int n,p,k,w[1<<20],ans;
signed main(){
	n=read(),p=read(),k=read();
	w[0]=1,w[1]=qpow(3,(mod-1)/k);
	for(int i=2;i<k;++i)w[i]=1ll*w[i-1]*w[1]%mod;
	ans=1ll*n*p%mod*qpow(p+1,n-1)%mod;
	int res=0;
	for(int i=0;i<k;++i){
		int x=qpow(1ll*p*w[i]%mod+1,n),y=0;
		if(i)y=1ll*k*qpow(w[k-i]-1,mod-2)%mod;
		else y=1ll*k*(k-1)/2%mod;
		res=(res+1ll*x*y%mod)%mod;
	}
	res=1ll*res*qpow(k,mod-2)%mod,ans=(ans+mod-res)%mod;
	ans=1ll*ans*qpow(k,mod-2)%mod;
	cout<<ans<<'\n';
}