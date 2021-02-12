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
const int N=200005;
const int M=N<<2;
int n,m;
int S2[M],zkyAK[M];
namespace math{
int fac[M],ifc[M],inv[M];
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
inline int comb(int n,int m){return n<m?0:1ll*fac[n]*ifc[m]%mod*ifc[n-m]%mod;}
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}
void initmath(const int&n=M-1){
	fac[0]=1;for(int i=1;i<=n;++i)fac[i]=1ll*i*fac[i-1]%mod;
	ifc[n]=qpow(fac[n],mod-2);for(int i=n-1;i>=0;--i)ifc[i]=1ll*(i+1)*ifc[i+1]%mod;
	inv[1]=1;for(int i=2;i<=n;++i)inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;

}
}
using namespace math;

namespace poly{

int rev[M],rt[M],lim;
void initpoly(const int&n){
	static int lg;
	for(lim=1,lg=0;lim<n;lim<<=1,++lg);
	for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
	for(int i=1;i<lim;i<<=1){
		int w=qpow(3,(mod-1)/(i<<1));rt[i]=1;
		for(int j=1;j<i;++j)rt[i+j]=1ll*rt[i+j-1]*w%mod;
	}
}
void NTT(int*a,int op){
	if(!op)reverse(a+1,a+lim);
	for(int i=0;i<lim;++i)if(i>rev[i])swap(a[i],a[rev[i]]);
	for(int i=1;i<lim;i<<=1){
		for(int j=0;j<lim;j+=i<<1){
			for(int k=0;k<i;++k){
				const int X=a[j+k],Y=1ll*rt[i+k]*a[i+j+k]%mod;
				fmod(a[j+k]=X+Y),fmod(a[i+j+k]=X-Y+mod);
			}
		}
	}
	if(!op)for(int i=0,iv=qpow(lim,mod-2);i<lim;++i)a[i]=1ll*iv*a[i]%mod;
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
	for(int i=0;i<lim;++i)g[i]=1ll*g[i]*(2+mod-1ll*A[i]*g[i]%mod)%mod;
	NTT(g,0),clr(g+n,lim-n);
}
void dao(int*g,int*f,int n){
	for(int i=0;i<n;++i)g[i]=1ll*f[i+1]*(i+1)%mod;g[n-1]=0;
}
void jif(int*g,int*f,int n){
	for(int i=1;i<=n;++i)g[i]=1ll*f[i-1]*inv[i]%mod;g[0]=0;
}
void poly_ln(int*g,int*f,int n){
	static int A[M];
	clr(A,n),poly_inv(A,f,n),dao(g,f,n),poly_mul(A,g,A,n,n),jif(g,A,n);
}
void poly_exp(int*g,int*f,int n){
	static int A[M];
	if(n==1)return g[0]=1,void();
	poly_exp(g,f,(n+1)>>1);
	poly_ln(A,g,n);
	A[0]=1;for(int i=1;i<n;++i)A[i]=(f[i]-A[i]+mod)%mod;
	poly_mul(A,g,g,n,n),clr(g+n,lim-n);
}
void stirling2_row(int*g,int n){
	static int A[M];
	for(int i=0;i<=n;++i)A[i]=1ll*qpow(i,n)*ifc[i]%mod;
	for(int i=0;i<=n;++i)g[i]=i&1?mod-ifc[i]:ifc[i];
	poly_mul(A,g,A,n+1,n+1);
	cpy(g,A,n+1);
}
void initpart4(int*g,int n,int m){
	static int A[M];
	clr(A,n);
	for(int i=1;i<=m;++i)
		for(int j=1;i*j<n;++j)
			fmod(A[i*j]+=inv[j]);
	clr(g,n),poly_exp(g,A,n);
}

}

void solve1(){printf("%d\n",qpow(m,n));}
void solve2(){printf("%lld\n",1ll*comb(m,n)*fac[n]%mod);}
void solve3(){printf("%lld\n",1ll*fac[m]*S2[m]%mod);}
void solve4(){
	int res=0;
	for(int i=1;i<=m;++i)res=(res+S2[i])%mod;
	printf("%d\n",res);
}
void solve5(){printf("%d\n",n<=m?1:0);}
void solve6(){printf("%d\n",S2[m]);}
void solve7(){printf("%d\n",comb(n+m-1,m-1));}
void solve8(){printf("%d\n",comb(m,n));}
void solve9(){printf("%d\n",n<m?0:comb(n-1,m-1));}
void solve10(){printf("%d\n",zkyAK[n]);}
void solve11(){printf("%d\n",n>m?0:1);}
void solve12(){printf("%d\n",n<m?0:zkyAK[n-m]);}
signed main(){
	initmath();
	n=read(),m=read();
	poly::stirling2_row(S2,n);
	poly::initpart4(zkyAK,n+1,m);
	solve1(),solve2(),solve3(),solve4(),solve5(),solve6(),
	solve7(),solve8(),solve9(),solve10(),solve11(),solve12();
}