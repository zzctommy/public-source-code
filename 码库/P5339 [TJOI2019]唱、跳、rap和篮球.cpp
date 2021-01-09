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
const int N=2005;
const int M=N<<2;
#define mod 998244353
namespace math{
int inv[N],fac[N],ifc[N];
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}
inline int binom(int n,int m){return n<m?0:1ll*fac[n]*ifc[m]%mod*ifc[n-m]%mod;}
void initmath(const int&n=N-5){
	inv[1]=1;for(int i=2;i<=n;++i)inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
	fac[0]=1;for(int i=1;i<=n;++i)fac[i]=1ll*fac[i-1]*i%mod;
	ifc[n]=qpow(fac[n],mod-2);for(int i=n-1;i>=0;--i)ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
}

}
using math::qpow;
using math::fmod;

namespace poly{
int rev[M],lg,lim;
void init_poly(const int&n){
	for(lim=1,lg=0;lim<n;lim<<=1,++lg);
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
				const int X=a[j+k],Y=1ll*w0*a[i+j+k]%mod;
				fmod(a[j+k]=X+Y),fmod(a[i+j+k]=X-Y+mod);
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
int calch(int index,int a,int b,int c,int d){
	static int A[M],B[M],C[M],D[M];
	init_poly(a+b+c+d);
	for(int i=0;i<a;++i)A[i]=math::ifc[i];clr(A+a,lim-a);
	for(int i=0;i<b;++i)B[i]=math::ifc[i];clr(B+b,lim-b);
	for(int i=0;i<c;++i)C[i]=math::ifc[i];clr(C+c,lim-c);
	for(int i=0;i<d;++i)D[i]=math::ifc[i];clr(D+d,lim-d);
	NTT(A,1),NTT(B,1),NTT(C,1),NTT(D,1);
	for(int i=0;i<lim;++i)A[i]=1ll*A[i]*B[i]%mod*C[i]%mod*D[i]%mod;
	NTT(A,0);return A[index];
}

}
int n,a,b,c,d,h[255],up,f[255],ans;
signed main(){
	math::initmath();
	n=read(),a=read(),b=read(),c=read(),d=read(),up=min(n>>2,min(a,min(b,min(c,d))));
	for(int i=0;i<=up;++i)h[i]=poly::calch(n-4*i,a-i+1,b-i+1,c-i+1,d-i+1);
	for(int i=0;i<=up;++i)f[i]=1ll*math::binom(n-3*i,i)*h[i]%mod*math::fac[n-4*i]%mod;
	for(int i=0;i<=up;++i)fmod(ans+=i&1?mod-f[i]:f[i]);
	printf("%d\n",ans);
	return 0;
}