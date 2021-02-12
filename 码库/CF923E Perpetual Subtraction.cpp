// Problem: CF923E Perpetual Subtraction
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF923E
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int N=100005;
const int M=N<<2;
#define mod 998244353

namespace math{
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
int fac[N],ifc[N],inv[N];
void initmath(const int&n=N-1){
	fac[0]=1;for(int i=1;i<=n;++i)fac[i]=1ll*i*fac[i-1]%mod;
	ifc[n]=qpow(fac[n],mod-2);for(int i=n-1;i>=0;--i)ifc[i]=1ll*(i+1)*ifc[i+1]%mod;
	inv[1]=1;for(int i=2;i<=n;++i)inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
}

}

using math::qpow;

namespace poly{
	
int rev[M],lg,lim;
void init_poly(const int&n){
	for(lg=0,lim=1;lim<n;lim<<=1,++lg);
	for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
}
void NTT(int*a,int op){
	for(int i=0;i<lim;++i)
		if(i>rev[i])swap(a[i],a[rev[i]]);
	const int g=op?3:math::inv[3];
	for(int i=1;i<lim;i<<=1){
		const int wn=qpow(g,(mod-1)/(i<<1));
		for(int j=0;j<lim;j+=i<<1){
			int w0=1;
			for(int k=0;k<i;++k,w0=1ll*w0*wn%mod){
				const int X=a[j+k],Y=1ll*a[i+j+k]*w0%mod;
				a[j+k]=(X+Y)%mod,a[i+j+k]=(X+mod-Y)%mod;
			}
		}
	}
	if(op)return;const int ilim=qpow(lim,mod-2);
	for(int i=0;i<lim;++i)a[i]=1ll*a[i]*ilim%mod;
}
#define clr(a,n) memset(a,0,sizeof(int)*(n))
#define cpy(a,b,n) memcpy(a,b,sizeof(int)*(n))
void poly_mul(int*f,int*g,int*ans,int n,int m){
	static int A[M],B[M];init_poly(n+m);
	cpy(A,f,n),clr(A+n,lim-n),NTT(A,1);
	cpy(B,g,m),clr(B+m,lim-m),NTT(B,1);
	for(int i=0;i<lim;++i)ans[i]=1ll*A[i]*B[i]%mod;
	NTT(ans,0);
}

}

int n,p[N],A[M],B[M],g[M],f[M];
LL m;
signed main(){
	math::initmath();scanf("%d%lld",&n,&m);
	for(int i=0;i<=n;++i)p[i]=read();
	for(int i=0;i<=n;++i)A[i]=1ll*math::fac[i]*p[i]%mod;
	for(int i=0;i<=n;++i)B[i]=math::ifc[n-i];
	poly::poly_mul(A,B,A,n+1,n+1);
	for(int i=0;i<=n;++i)g[i]=1ll*A[n+i]*math::ifc[i]%mod;
	
	m%=mod-1;
	for(int i=0;i<=n;++i)g[i]=1ll*g[i]*qpow(math::inv[i+1],m)%mod;
	
	for(int i=0;i<=n;++i)A[i]=1ll*math::fac[i]*g[i]%mod*(i&1?mod-1:1)%mod;
	for(int i=0;i<=n;++i)B[i]=math::ifc[n-i];
	poly::poly_mul(A,B,A,n+1,n+1);
	for(int i=0;i<=n;++i)f[i]=1ll*A[n+i]*(i&1?mod-math::ifc[i]:math::ifc[i])%mod;
	
	for(int i=0;i<=n;++i)printf("%d ",f[i]);
	return 0;
}