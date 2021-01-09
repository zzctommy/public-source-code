const int N=100005;
const int M=N<<2;
#define mod 998244353
namespace math{
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}
int fac[N],ifc[N],inv[N];
void initmath(const int&n=N-1){
	fac[0]=1;for(int i=1;i<=n;++i)fac[i]=1ll*i*fac[i-1]%mod;
	ifc[n]=qpow(fac[n],mod-2);for(int i=n-1;i>=0;--i)ifc[i]=1ll*(i+1)*ifc[i+1]%mod;
	inv[1]=1;for(int i=2;i<=n;++i)inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
}
}
using math::qpow;
using math::fmod;

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
				const int X=a[j+k],Y=1ll*w0*a[i+j+k]%mod;
				fmod(a[j+k]=X+Y),fmod(a[i+j+k]=mod+X-Y);
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
void poly_inv(int*g,int*f,int n){
	static int A[M];
	if(n==1)return g[0]=qpow(f[0],mod-2),void();
	poly_inv(g,f,(n+1)>>1);
	init_poly(n<<1);
	cpy(A,f,n),clr(A+n,lim-n),clr(g+n,lim-n);
	NTT(A,1),NTT(g,1);
	for(int i=0;i<lim;++i)g[i]=1ll*g[i]*(2-1ll*g[i]*A[i]%mod+mod)%mod;
	NTT(g,0),clr(g+n,lim-n);
}
void poly_sqrt(int*g,int*f,int pw){
	static int A[M];
	if(pw==1)return g[0]=1,void();
	poly_sqrt(g,f,(pw+1)>>1);
	clr(A,pw),poly_inv(A,g,pw),poly_mul(A,f,A,pw,pw);
	for(int i=0,iv2=math::inv[2];i<pw;++i)g[i]=1ll*(g[i]+A[i])*iv2%mod;
}
void dao(int*g,int*f,int n){
	for(int i=0;i<n-1;++i)g[i]=1ll*f[i+1]*(i+1)%mod;g[n-1]=0;
}
void jif(int*g,int*f,int n){
	for(int i=1;i<=n;++i)g[i]=1ll*f[i-1]*math::inv[i]%mod;g[0]=0;
}
void poly_ln(int*g,int*f,int n){
	static int A[M],B[M];
	dao(A,f,n),clr(B,n),poly_inv(B,f,n),poly_mul(A,B,A,n,n),jif(g,A,n);
}
void poly_exp(int*g,int*f,int n){
	static int A[M];
	if(n==1)return g[0]=1,void();
	poly_exp(g,f,(n+1)>>1);
	clr(A,n),poly_ln(A,g,n);
	for(int i=0;i<n;++i)fmod(A[i]=(!i)-A[i]+f[i]+mod);
	poly_mul(A,g,g,n,n),clr(g+n,lim-n);
}
void poly_qpow(int*g,int*f,int n,int k){
	static int A[M];
	clr(A,n),poly_ln(A,f,n);
	for(int i=0;i<n;++i)A[i]=1ll*A[i]*k%mod;
	clr(g,n),poly_exp(g,A,n);
}

}