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
const int N=200005;
const int M=N<<2;
const int K=20000005;
#define mod 998244353
int n,m,s,l,sti[N],k,ans;
namespace math{
int fac[K],ifc[K];
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}
inline int comb(int n,int m){return n<m?0:1ll*fac[n]*ifc[m]%mod*ifc[n-m]%mod;}
void initmath(const int&n=K-1){
	fac[0]=1;for(int i=1;i<=n;++i)fac[i]=1ll*i*fac[i-1]%mod;
	ifc[n]=qpow(fac[n],mod-2);for(int i=n-1;i>=0;--i)ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
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
	const int g=op?3:qpow(3,mod-2);
	for(int i=1;i<lim;i<<=1){
		const int wn=qpow(g,(mod-1)/(i<<1));
		for(int j=0;j<lim;j+=i<<1){
			int w0=1;
			for(int k=0;k<i;++k,w0=1ll*w0*wn%mod){
				const int X=a[j|k],Y=1ll*w0*a[i|j|k]%mod;
				fmod(a[j|k]=X+Y),fmod(a[i|j|k]=X-Y+mod);
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
void get_stirling(int n,int*sti){//第n行
	static int A[M],B[M];
	for(int i=0;i<=n;++i)A[i]=i&1?mod-math::ifc[i]:math::ifc[i],B[i]=1ll*qpow(i,n)*math::ifc[i]%mod;
	poly_mul(A,B,A,n+1,n+1);
	for(int i=0;i<=n;++i)sti[i]=A[i];
}

}
signed main(){
	n=read(),m=read(),s=read(),l=read();
	math::initmath(n);
	poly::get_stirling(l,sti);
	while(s--){
		n=read(),m=read(),k=read(),ans=0;
		for(int up=min(n,min(m,l)),i=0;i<=up;++i){
			fmod(ans+=1ll*math::fac[i]*sti[i]%mod*math::comb(m,i)%mod*math::comb(n-i,k-i)%mod);
		}
		ans=1ll*ans*qpow(math::comb(n,k),mod-2)%mod;
		printf("%d\n",ans);
	}
	return 0;
}