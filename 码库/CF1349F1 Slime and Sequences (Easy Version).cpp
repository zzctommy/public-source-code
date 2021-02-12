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
const int N=5005;
int o[N][N],n,ans[N],fac[N],ifc[N];
inline int comb(int n,int m){return n<m?0:1ll*fac[n]*ifc[m]%mod*ifc[n-m]%mod;}
signed main(){
	n=read();
	o[0][0]=1;
	rep(i,1,n)rep(j,0,i-1){
		o[i][j]=1ll*o[i-1][j]*(j+1)%mod;
		if(j>0)o[i][j]=(1ll*o[i-1][j-1]*(i-j)%mod+o[i][j])%mod;
	}
	fac[0]=1;rep(i,1,n)fac[i]=1ll*fac[i-1]*i%mod;
	ifc[n]=qpow(fac[n],mod-2);per(i,n-1,0)ifc[i]=1ll*(i+1)*ifc[i+1]%mod;
	rep(k,1,n)rep(i,1,n)ans[k]=(ans[k]+1ll*fac[n-i]*o[i][k-1]%mod*comb(n,i)%mod)%mod;
	rep(i,1,n)printf("%d%c",ans[i]," \n"[i==n]);
	return 0;
}