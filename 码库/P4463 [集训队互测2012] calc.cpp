/*

    |-------                                                    |-----|                                   
    |                                                           |     | 
    |                                                           |     |
    |                                                           |     |                             *    |
    |------ |----|   ---  -----  \       / -----   ---          |-----| |    |   ---  ----- |    |     --|--
    |       |    | |/   \ |   |   \     /  |   | |/   \         |       |    | |/   \ |     |    |  |    |  
    |       |    | |      -----    \   /   ----- |              |       |    | |      |---- |    |  |    |
    |       |    | |      |         \ /    |     |              |       |    | |          | |    |  |    |
    |       |----| |      ----/      -     ---/  |      _____   |       |----| |      ----| |----|  |    --/


    \       /  \       / |----\     ------
     \     /    \     /  |     \    |
      \   /      \   /   |      \   |
       \-/        \-/    |      |   ------
        |          |     |      |        |
        |          |     |      /        |
        |          |     |     /         |
        |          |     |----/     ------


*/
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
const int N=505;
int k,n,mod,f[N],g[N];
namespace math{
int fac[N],ifc[N],inv[N];
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
void initmath(const int&n=N-1){
	fac[0]=1;for(int i=1;i<=n;++i)fac[i]=1ll*i*fac[i-1]%mod;
	ifc[n]=qpow(fac[n],mod-2);for(int i=n-1;i>=0;--i)ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
	inv[1]=1;for(int i=2;i<=n;++i)inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
}
}
using math::qpow;
using math::fmod;

int lagrange(int n,int k){//前n项k次幂和
	static int pre[N],suf[N],sum[N],res;
	sum[0]=res=0;
	rep(i,1,k+2)fmod(sum[i]=sum[i-1]+qpow(i,k));
	if(n<=k+2)return sum[n];
	pre[0]=1;for(int i=1;i<=k+2;++i)pre[i]=1ll*pre[i-1]*(n-i)%mod;
	suf[k+3]=1;for(int i=k+2;i>=1;--i)suf[i]=1ll*suf[i+1]*(n-i)%mod;
	for(int i=1;i<=k+2;++i){
		int A=1ll*pre[i-1]*suf[i+1]%mod;
		int B=1ll*math::ifc[i-1]*math::ifc[k+2-i]%mod;
		if((k+2-i)&1)B=mod-B;
		fmod(res+=1ll*A*B%mod*sum[i]%mod);
	}
	return res;
}
void poly_exp(int*g,int*f,int n){
	g[0]=1;
	for(int i=1;i<n;++i){
		g[i]=0;
		for(int j=0;j<i;++j)fmod(g[i]+=1ll*(j+1)*f[j+1]%mod*g[i-1-j]%mod);
		g[i]=1ll*g[i]*math::inv[i]%mod;
	}
}
signed main(){
	k=read(),n=read(),mod=read(),math::initmath();
	for(int i=1;i<=n;++i)f[i]=1ll*lagrange(k,i)*(i&1?math::inv[i]:mod-math::inv[i])%mod;
	poly_exp(g,f,n+1);
	printf("%lld\n",1ll*g[n]*math::fac[n]%mod);
	return 0;
}