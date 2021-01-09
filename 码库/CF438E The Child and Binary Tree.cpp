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
const int N=100005;
const int M=N<<2;

namespace math{

int inv[N];
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}
void initmath(const int&n=N-5){
	inv[1]=1;for(int i=2;i<=n;++i)inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
}

}
using math::qpow;
using math::fmod;

namespace poly{

int lim,lg,rev[M];
void init_poly(const int&n){
	for(lim=1,lg=0;lim<=n;lim<<=1,++lg);
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
				const int X=a[j+k],Y=1ll*a[i+j+k]*w0%mod;
				fmod(a[j+k]=X+Y),fmod(a[i+j+k]=X-Y+mod);
			}
		}
	}
	if(op)return;int ilim=qpow(lim,mod-2);
	for(int i=0;i<lim;++i)a[i]=1ll*ilim*a[i]%mod;
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
void poly_sqrt(int*g,int*f,int n){
	static int A[M],B[M];
	if(n==1)return g[0]=1,void();
	poly_sqrt(g,f,(n+1)>>1);
	clr(A,n),poly_inv(A,g,n),poly_mul(f,A,A,n,n);
	for(int i=0,iv=math::inv[2];i<n;++i)g[i]=1ll*(g[i]+A[i])*iv%mod;
}

}

int n,m,f[M],g[M],ans[M];

signed main(){
	n=read(),m=read()+1,math::initmath(),g[0]=1;
	for(int i=1,x;i<=n;++i)if((x=read())<m)g[x]=1;
	for(int i=1;i<m;++i)fmod(g[i]=mod-4ll*g[i]%mod);
	poly::poly_sqrt(f,g,m),fmod(++f[0]);
	poly::poly_inv(ans,f,m);
	for(int i=0;i<m;++i)fmod(ans[i]<<=1);
	for(int i=1;i<m;++i)printf("%d\n",ans[i]);
	return 0;
}