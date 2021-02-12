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
int inv[N],fac[N],ifc[N];
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
void fmod(int&x){x-=mod,x+=x>>31&mod;}
void initmath(const int&n=N-1){
	inv[1]=1;for(int i=2;i<=n;++i)inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
	fac[0]=1;for(int i=1;i<=n;++i)fac[i]=1ll*i*fac[i-1]%mod;
	ifc[n]=qpow(fac[n],mod-2);for(int i=n-1;i>=0;--i)ifc[i]=1ll*(i+1)*ifc[i+1]%mod;
}
}
using math::qpow;
using math::fmod;

namespace poly{

int rev[M],lg,lim;
void init_poly(const int&n){
	for(lg=0,lim=1;lim<=n;++lg,lim<<=1);
	for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
}
void NTT(int*a,int op){
	for(int i=0;i<lim;++i)
		if(i>rev[i])swap(a[i],a[rev[i]]);
	const int g=op?3:qpow(3,mod-2);
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
void poly_inv(int*g,int*f,int n){
	static int A[M];
	if(n==1)return g[0]=qpow(f[0],mod-2),void();
	poly_inv(g,f,(n+1)>>1),init_poly(n<<1);
	cpy(A,f,n),clr(A+n,lim-n),clr(g+n,lim-n);
	NTT(A,1),NTT(g,1);
	for(int i=0;i<lim;++i)g[i]=1ll*g[i]*(2-1ll*A[i]*g[i]%mod+mod)%mod;
	NTT(g,0),clr(g+n,lim-n);
}
void poly_sqrt(int*g,int*f,int pw){
	static int A[M];
	if(pw==1)return g[0]=1,void();
	poly_sqrt(g,f,(pw+1)>>1);
	clr(A,pw),poly_inv(A,g,pw),poly_mul(A,f,A,pw,pw);
	for(int i=0,iv2=math::inv[2];i<pw;++i)g[i]=1ll*(g[i]+A[i])*iv2%mod;
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
void stirling2_row(int*g,int n){//注意！这个函数左闭右闭
	static int A[M],B[M];
	for(int i=0;i<=n;++i)A[i]=1ll*qpow(i,n)*math::ifc[i]%mod;
	for(int i=0;i<=n;++i)B[i]=i&1?mod-math::ifc[i]:math::ifc[i];
	poly_mul(A,B,A,n+1,n+1);
	for(int i=0;i<=n;++i)g[i]=A[i];
}
void poly_shift(int*g,int*f,int n,int c){
	static int A[M],B[M];
	for(int i=0;i<n;++i)A[i]=1ll*math::fac[i]*f[i]%mod;
	for(int i=0,j=1;i<n;++i,j=1ll*j*c%mod)B[i]=1ll*j*math::ifc[i]%mod;
	reverse(B,B+n),poly_mul(A,B,A,n,n);
	for(int i=0;i<n;++i)g[i]=1ll*A[n+i-1]*math::ifc[i]%mod;
}
void up_pow(int*g,int n){//注意！这个函数左闭右闭
	static int A[M];
	if(n==1)return g[0]=0,g[1]=1,void();
	if(n&1){
		up_pow(g,n-1);
		for(int i=n;i>0;--i)g[i]=(g[i-1]+1ll*(n-1)*g[i]%mod)%mod;
	}else{
		up_pow(g,n/2);
		clr(A,n/2+1),poly_shift(A,g,n/2+1,n/2),poly_mul(A,g,g,n/2+1,n/2+1);
	}
}
void stirling1_row(int*g,int n){up_pow(g,n);}//注意！这个函数左闭右闭
void stirling1_column(int*g,int n,int k){//注意！这个函数左闭右闭
	if(n<k){
		for(int i=0;i<=n;++i)g[i]=0;
		return;
	}
	static int A[M];
	for(int i=0;i<=n;++i)A[i]=math::inv[i+1];
	clr(g,n+1),poly_qpow(g,A,k,n+1);
	for(int i=n;i>=k;--i)g[i]=g[i-k];
	for(int i=0;i<k;++i)g[i]=0;
	for(int i=k;i<=n;++i)g[i]=1ll*g[i]*math::fac[i]%mod*math::ifc[k]%mod;
}
void down_pow(int*g,int n){//注意！这个函数左闭右闭
	static int A[M];
	if(n==1)return g[0]=0,g[1]=1,void();
	if(n&1){
		down_pow(g,n-1);
		for(int i=n;i>0;--i)g[i]=(g[i-1]+1ll*(mod-n+1)*g[i]%mod)%mod;
	}else{
		down_pow(g,n/2);
		clr(A,n/2+1),poly_shift(A,g,n/2+1,mod-n/2),poly_mul(A,g,g,n/2+1,n/2+1);
	}
}
void stirling2_column(int*g,int n,int k){//注意！这个函数左闭右闭
	static int A[M];
	if(n<k){
		for(int i=0;i<=n;++i)g[i]=0;
		return;
	}
	clr(A,k+2),down_pow(A,k+1);
	for(int i=0;i<k+1;++i)A[i]=A[i+1];A[k+1]=0;
	reverse(A,A+k+1);
	clr(g,k+1),poly_inv(g,A,n-k+1);
	for(int i=n;i>=k;--i)g[i]=g[i-k];
	for(int i=0;i<k;++i)g[i]=0;
}
void bell(int*g,int n){
	static int A[M];A[0]=0;
	for(int i=1;i<n;++i)A[i]=math::ifc[i];
	clr(g,n),poly_exp(g,A,n);
	for(int i=0;i<n;++i)g[i]=1ll*g[i]*math::fac[i]%mod;
}

}

int n,g[M];

signed main(){
	math::initmath();
	poly::bell(g,100001);
	for(int T=read();T;--T)printf("%d\n",g[read()]);
	return 0;
}
/*
5
2
3
7
9
233

*/