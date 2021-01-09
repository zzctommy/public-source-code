#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef long double db;
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
const int N=600005;
int n,k,a[N],q,ans[N],cnt[N];

namespace math{

inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}

int pw2[N],fac[N],ifc[N],inv[N];
void initmath(const int&n=600000){
	pw2[0]=1;for(int i=1;i<=n;++i)fmod(pw2[i]=pw2[i-1]<<1);
	fac[0]=1;for(int i=1;i<=n;++i)fac[i]=1ll*i*fac[i-1]%mod;
	ifc[n]=qpow(fac[n],mod-2);for(int i=n-1;i>=0;--i)ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
	inv[1]=1;for(int i=2;i<=n;++i)inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
}
int binom(int n,int m){return n<m?0:1ll*fac[n]*ifc[m]%mod*ifc[n-m]%mod;}

}

namespace poly{

using math::qpow;
using math::fmod;
const int M=N<<2;
int lim,rev[M],lg;
void init_poly(const int&n){
	for(lg=0,lim=1;lim<n;++lg,lim<<=1);
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
	if(op)return;int ilim=qpow(lim,mod-2);
	for(int i=0;i<lim;++i)a[i]=1ll*a[i]*ilim%mod;
}
#define clr(a,n) memset(a,0,sizeof(int)*(n))
#define cpy(a,b,n) memcpy(a,b,sizeof(int)*(n))
void poly_mul(int*f,int*g,int*h,int n,int m){
	static int A[M],B[M];init_poly(n+m);
	cpy(A,f,n),clr(A+n,lim-n),NTT(A,1);
	cpy(B,g,m),clr(B+m,lim-m),NTT(B,1);
	for(int i=0;i<lim;++i)h[i]=1ll*A[i]*B[i]%mod;
	NTT(h,0);
}
void solve(int up){
	static int x,y,A[M],B[M];
	x=y=0;
	for(int i=1;i<up;++i)
		if(cnt[i]==1)++x;
		else if(cnt[i]>=2)++y;
	y<<=1;
	for(int i=0;i<=x;++i)A[i]=1ll*math::pw2[i]*math::binom(x,i)%mod;
	for(int i=0;i<=y;++i)B[i]=math::binom(y,i);
	poly_mul(A,B,A,x+1,y+1);
	for(int i=0;i<=min(x+y,N-5);++i)fmod(ans[i+up+1]+=A[i]);
}

}

signed main(){
	n=read(),k=read(),math::initmath();
	for(int i=1;i<=n;++i)++cnt[a[i]=read()];
	for(int i=1;i<=k;++i)poly::solve(read());
	q=read();
	for(int i=1;i<=q;++i)printf("%d\n",ans[read()>>1]);
	return 0;
}