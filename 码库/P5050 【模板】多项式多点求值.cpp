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
const int N=64005;
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
using namespace math;

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
	for(int i=0;i<lim;++i)A[i]=1ll*A[i]*B[i]%mod;
	NTT(A,0),cpy(ans,A,n+m-1);
}
void poly_inv(int*g,int*f,int n){
	static int A[M],B[M];
	if(n==1)return g[0]=qpow(f[0],mod-2),void();
	int m=(n+1)>>1;
	poly_inv(g,f,m),initpoly(n<<1);
	cpy(A,f,n),clr(A+n,lim-n),cpy(B,g,m),clr(B+m,lim-m);
	NTT(A,1),NTT(B,1);
	for(int i=0;i<lim;++i)A[i]=1ll*B[i]*(2-1ll*A[i]*B[i]%mod+mod)%mod;
	NTT(A,0),cpy(g,A,n);
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
	reverse(F,F+n),reverse(G,G+m);
	poly_inv(A,G,n-m+1),poly_mul(F,A,A,n-m+1,n-m+1);
	for(int i=0;i<n-m+1;++i)Q[i]=A[n-m-i];
	reverse(F,F+n),reverse(G,G+m),poly_mul(G,Q,A,m,n-m+1);
	for(int i=0;i<m-1;++i)fmod(R[i]=F[i]+mod-A[i]);
}

#define lc (p<<1)
#define rc (p<<1|1)
int pool[N<<6],*mem=pool,*ev[M];
void eva_mul(int*f,int*g,int*ans,int n,int m){
	static int A[M],B[M];initpoly(n);
	cpy(A,f,n),clr(A+n,lim-n),NTT(A,1);
	cpy(B,g,m),clr(B+m,lim-m),NTT(B,1);
	for(int i=0;i<lim;++i)A[i]=1ll*A[i]*B[i]%mod;
	NTT(A,0),cpy(ans,A+m-1,n-m+1);
}
void eva_solve1(int l,int r,int p,int*a){
	ev[p]=mem,mem+=r-l+1;
	if(r-l==1)return ev[p][0]=mod-a[l],ev[p][1]=1,void();
	int mid=(l+r)>>1;
	eva_solve1(l,mid,lc,a);
	eva_solve1(mid,r,rc,a);
	poly_mul(ev[lc],ev[rc],ev[p],mid-l+1,r-mid+1);
}
void eva_solve2(int l,int r,int p,int*h,int*f){
	if(r-l==1)return h[l]=f[0],void();
	int mid=(l+r)>>1,*al,*ar;
	al=mem,mem+=mid-l,ar=mem,mem+=r-mid;
	eva_mul(f,ev[rc],al,r-l,r-mid+1);
	eva_mul(f,ev[lc],ar,r-l,mid-l+1);
	eva_solve2(l,mid,lc,h,al);
	eva_solve2(mid,r,rc,h,ar);
}
void poly_eva(int*g,int*f,int*a,int n,int m){
	static int A[M];
	n=max(n,m);
	eva_solve1(0,n,1,a);
	reverse(ev[1],ev[1]+n+1);
	poly_inv(A,ev[1],n),reverse(A,A+n);
	poly_mul(A,f,A,n,n),cpy(A,A+n,n);
	eva_solve2(0,n,1,g,A);
	for(int i=0;i<m;++i)fmod(g[i]=1ll*g[i]*a[i]%mod+f[0]);
	for(int i=m;i<n;++i)g[i]=0;
}

}
int f[M],a[M],g[M],n,m;
signed main(){
	n=read()+1,m=read();
	for(int i=0;i<n;++i)f[i]=read();
	for(int i=0;i<m;++i)a[i]=read();
	poly::poly_eva(g,f,a,n,m);
	for(int i=0;i<m;++i)printf("%d\n",g[i]);
	return 0;
}