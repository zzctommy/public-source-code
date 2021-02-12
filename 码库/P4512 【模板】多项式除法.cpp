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
const int M=N<<2;
#define mod 998244353
namespace math{
int inv[N],fac[N],ifc[N];
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}
void initmath(const int&n=N-1){
	inv[1]=1;for(int i=2;i<=n;++i)inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
	fac[0]=1;for(int i=1;i<=n;++i)fac[i]=1ll*i*fac[i-1]%mod;
	ifc[n]=qpow(fac[n],mod-2);for(int i=n-1;i>=0;--i)ifc[i]=1ll*(i+1)*ifc[i+1]%mod;
}
}
using math::qpow;
using math::fmod;

namespace poly{

int rev[M],lg,lim,rt[M];
void initpoly(const int&n){
	for(lg=0,lim=1;lim<=n;++lg,lim<<=1);
	for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
	for(int i=1;i<lim;i<<=1){
		const int w=qpow(3,(mod-1)/(i<<1));
		rt[i]=1;
		for(int j=1;j<i;++j)rt[i+j]=1ll*rt[i+j-1]*w%mod;
	}
}
void NTT(int*a,int op){
	if(!op)reverse(a+1,a+lim);
	for(int i=0;i<lim;++i)
		if(i>rev[i])swap(a[i],a[rev[i]]);
	for(int i=1;i<lim;i<<=1){
		for(int j=0;j<lim;j+=i<<1){
			for(int k=0;k<i;++k){
				const int X=a[j+k],Y=1ll*rt[i+k]*a[i+j+k]%mod;
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
	static int A[M],B[M];initpoly(n+m);
	cpy(A,f,n),clr(A+n,lim-n),NTT(A,1);
	cpy(B,g,m),clr(B+m,lim-m),NTT(B,1);
	for(int i=0;i<lim;++i)ans[i]=1ll*A[i]*B[i]%mod;
	NTT(ans,0);
}
void poly_inv(int*g,int*f,int n){
	static int A[M];
	if(n==1)return g[0]=qpow(f[0],mod-2),void();
	poly_inv(g,f,(n+1)>>1),initpoly(n<<1);
	cpy(A,f,n),clr(A+n,lim-n),clr(g+n,lim-n);
	NTT(A,1),NTT(g,1);
	for(int i=0;i<lim;++i)g[i]=1ll*g[i]*(2-1ll*A[i]*g[i]%mod+mod)%mod;
	NTT(g,0),clr(g+n,lim-n);
}
void poly_sqrt(int*g,int*f,int n){
	static int A[M];
	if(n==1)return g[0]=1,void();
	poly_sqrt(g,f,(n+1)>>1);
	clr(A,n),poly_inv(A,g,n),poly_mul(A,f,A,n,n);
	for(int i=0,iv2=math::inv[2];i<n;++i)g[i]=1ll*(g[i]+A[i])*iv2%mod;
}
void jif(int*g,int*f,int n){
	for(int i=1;i<=n;++i)g[i]=1ll*f[i-1]*math::inv[i]%mod;g[0]=0;
}
void dao(int*g,int*f,int n){
	for(int i=0;i<n-1;++i)g[i]=1ll*(i+1)*f[i+1]%mod;g[n-1]=0;
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
	for(int i=0;i<n;++i)fmod(A[i]=(!i)+f[i]-A[i]+mod);
	poly_mul(g,A,g,n,n),clr(g+n,lim-n);
}
void poly_qpow(int*g,int *f,int k,int n){
	static int A[M];
	clr(A,n),poly_ln(A,f,n);
	for(int i=0;i<n;++i)A[i]=1ll*A[i]*k%mod;
	poly_exp(g,A,n);
}
void poly_div(int*Q,int*R,int*F,int*G,int n,int m){
	static int A[M];
	reverse(F,F+n),reverse(G,G+m),poly_inv(A,G,n-m+1),poly_mul(F,A,A,n-m+1,n-m+1);
	for(int i=0;i<n-m+1;++i)Q[i]=A[n-m-i];
	reverse(F,F+n),reverse(G,G+m),poly_mul(G,Q,A,m,n-m+1);
	for(int i=0;i<m-1;++i)fmod(R[i]=F[i]+mod-A[i]);
}

}
int n,m,F[M],G[M],Q[M],R[M];
signed main(){
	n=read()+1,m=read()+1;
	for(int i=0;i<n;++i)F[i]=read();
	for(int i=0;i<m;++i)G[i]=read();
	poly::poly_div(Q,R,F,G,n,m);
	for(int i=0;i<n-m+1;++i)printf("%d ",Q[i]);puts("");
	for(int i=0;i<m-1;++i)printf("%d ",R[i]);puts("");
	return 0;
}