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

#define mod 1004535809
const int V=10000005;
const int N=100005;
const int M=N<<2;

namespace math{
int fac[V],ifc[V];
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}
int binom(int n,int m){return n<m?0:1ll*fac[n]*ifc[m]%mod*ifc[n-m]%mod;}
void initmath(const int&n=V-1){
	fac[0]=1;for(int i=1;i<=n;++i)fac[i]=1ll*i*fac[i-1]%mod;
	ifc[n]=qpow(fac[n],mod-2);for(int i=n-1;i>=0;--i)ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
}

}
using math::qpow;
using math::fmod;

namespace poly{
int rev[M],lg,lim;
void poly_init(const int&n){
	for(lg=0,lim=1;lim<n;++lg,lim<<=1);
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
				const int X=a[j+k],Y=1ll*a[i+j+k]*w0%mod;
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
	static int A[M],B[M];poly_init(n+m);
	cpy(A,f,n),clr(A+n,lim-n),NTT(A,1);
	cpy(B,g,m),clr(B+m,lim-m),NTT(B,1);
	for(int i=0;i<lim;++i)ans[i]=1ll*A[i]*B[i]%mod;
	NTT(ans,0);
}

}

int n,m,S,up,f[M],g[M],A[M],B[M],C[M],W[N],ans;
signed main(){
	math::initmath();
	n=read(),m=read(),S=read(),up=min(n/S,m);
	rep(i,0,m)W[i]=read();
	for(int i=0;i<=up;++i)f[i]=1ll*math::binom(m,i)*math::fac[n]%mod*qpow(math::ifc[S],i)%mod*math::ifc[n-S*i]%mod*qpow(m-i,n-S*i)%mod;
	for(int i=0;i<=up;++i)A[i]=1ll*math::fac[up-i]*f[up-i]%mod;
	for(int i=0;i<=up;++i)B[i]=(i&1)?mod-math::ifc[i]:math::ifc[i];
	poly::poly_mul(A,B,C,up+1,up+1);
	for(int i=0;i<=up;++i)g[i]=1ll*math::ifc[i]*C[up-i]%mod;
	for(int i=0;i<=up;++i)fmod(ans+=1ll*g[i]*W[i]%mod);
	printf("%d\n",ans);
	return 0;
}