//Orz cyn2006
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
const int N=30005;
const int M=N<<2;
const int mod=1e9+7;
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
int n,k,f[M],ans;
namespace poly{
const db pi=acos(-1.0);
int rev[M],lg,lim;
int fac[M],ifc[M];
void initmath(const int&n){
	fac[0]=1;for(int i=1;i<=n;++i)fac[i]=1ll*i*fac[i-1]%mod;
	ifc[n]=qpow(fac[n],mod-2);for(int i=n-1;i>=0;--i)ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
}
struct cp{
	db x,y;
	cp(){x=y=0;}
	cp(db x_,db y_){x=x_,y=y_;}
	cp operator + (const cp&t)const{return cp(x+t.x,y+t.y);}
	cp operator - (const cp&t)const{return cp(x-t.x,y-t.y);}
	cp operator * (const cp&t)const{return cp(x*t.x-y*t.y,x*t.y+y*t.x);}
}w[M];
void init_poly(const int&n){
	for(lim=1,lg=0;lim<=n;lim<<=1,++lg);
	for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1)),w[i]=cp(cos(2.*pi*i/lim),sin(2.*pi*i/lim));
}
void FFT(cp*a,int op){
    for(int i=0;i<lim;++i)if(i>rev[i])swap(a[i],a[rev[i]]);
    for(int i=1,t=lim>>1;i<lim;i<<=1,t>>=1){
	    for(int j=0;j<lim;j+=i<<1){
		    for(int k=0;k<i;++k){
			    const cp X=a[j+k],Y=w[t*k]*a[i+j+k];
			    a[j+k]=X+Y,a[i+j+k]=X-Y;
			}
		}
	}
    if(!op)for(int i=0;i<lim;++i)a[i].x/=lim;
}
void MTT(int*f,int*g,int*ans){	
	static cp A[M],B[M],C[M],D[M],E[M],F[M],G[M];
	for(int i=0;i<lim;++i)
		A[i]=cp(f[i]&65535,0),B[i]=cp(f[i]>>16,0),
		C[i]=cp(g[i]&65535,0),D[i]=cp(g[i]>>16,0);
	FFT(A,1),FFT(B,1),FFT(C,1),FFT(D,1);
	for(int i=0;i<lim;++i)
		E[i]=A[i]*C[i],F[i]=A[i]*D[i]+B[i]*C[i],G[i]=B[i]*D[i],w[i].y*=-1;
	FFT(E,0),FFT(F,0),FFT(G,0);
	for(int i=0;i<lim;++i)
		ans[i]=LL(G[i].x+0.5)%mod,
		ans[i]=((65536ll*ans[i]%mod)+LL(F[i].x+0.5)%mod)%mod,
		ans[i]=((65536ll*ans[i]%mod)+LL(E[i].x+0.5)%mod)%mod,
		w[i].y*=-1;
}
#define clr(a,n) memset(a,0,sizeof(int)*(n))
#define cpy(a,b) memcpy(a,b,sizeof(int)*(n))
void shift(const int&n,const int&len){
	static int g[M],h[M];
	clr(g,lim),clr(h,lim);
	for(int i=0,bas=qpow(2,len),j=1;i<n;++i,j=1ll*j*bas%mod)g[i]=1ll*f[i]*j%mod*ifc[i]%mod;
	for(int i=1;i<=n;++i)h[i]=1ll*f[i]*ifc[i]%mod;
	MTT(g,h,f);
	for(int i=0;i<=n;++i)f[i]=1ll*f[i]*fac[i]%mod;
	clr(f+n+1,lim-n);
}
void setbit(const int&n){
	static int g[M],h[M];
	clr(g,lim),clr(h,lim);
	for(int i=0,j=1;i<n;++i,(j<<=1)%=mod)g[i]=1ll*f[i]*j%mod*ifc[i]%mod;
	for(int i=1;i<=n;++i)h[i]=ifc[i];
	MTT(g,h,f);
	for(int i=0;i<=n;++i)f[i]=1ll*f[i]*fac[i]%mod;
	clr(f+n+1,lim-n);
}
}
using poly::fac;
using poly::ifc;
signed main(){
	LL whatsthis;scanf("%lld%d",&whatsthis,&k);
	if(whatsthis>k)return puts("0"),0;
	n=whatsthis;
	f[0]=0;rep(i,1,k)f[i]=1;
	poly::init_poly(k<<1),poly::initmath(k);
	for(int i=log2(n)-1,len=1;i>=0;--i){
		poly::shift(k,len),len<<=1;
		if(n>>i&1)poly::setbit(k),++len;
	}
	for(int i=n;i<=k;++i)ans=(ans+1ll*f[i]*fac[k]%mod*ifc[i]%mod*ifc[k-i]%mod)%mod;
	printf("%d\n",ans);
	return 0;
} 