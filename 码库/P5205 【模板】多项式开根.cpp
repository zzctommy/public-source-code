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
#define mod 998244353
namespace math{
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
void fmod(int&x){x-=mod,x+=x>>31&mod;}
}
using namespace math;

namespace poly{

const int M=N<<2;
int rev[M],lg,lim;
void init_poly(const int&n){
	for(lg=0,lim=1;lim<=n;++lg,lim<<=1);
	for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
}
void NTT(int*a,int op){
	for(int i=0;i<lim;++i)
		if(i>rev[i])swap(a[i],a[rev[i]]);
	int g=op?3:qpow(3,mod-2);
	for(int i=1;i<lim;i<<=1){
		int wn=qpow(g,(mod-1)/(i<<1));
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
void poly_mul(int*f,int*g,int*ans,int n,int m){
	static int A[M],B[M];init_poly(n+m);
	cpy(A,f,n),clr(A+n,lim-n),NTT(A,1);
	cpy(B,g,m),clr(B+m,lim-m),NTT(B,1);
	for(int i=0;i<lim;++i)ans[i]=1ll*A[i]*B[i]%mod;
	NTT(ans,0);
}
void poly_inv(int*g,int*f,int pw){//f[0,n)的逆元存在g里面
	static int A[M];
	if(pw==1)return g[0]=qpow(f[0],mod-2),void();
	poly_inv(g,f,(pw+1)>>1),init_poly(pw<<1);
	cpy(A,f,pw),clr(A+pw,lim-pw);
	NTT(A,1),NTT(g,1);
	for(int i=0;i<lim;++i)g[i]=1ll*g[i]*(2-1ll*A[i]*g[i]%mod+mod)%mod;
	NTT(g,0),clr(g+pw,lim-pw);
}
void poly_sqrt(int*g,int*f,int pw){//f[0,n)的根号在g里面
	static int A[M];
	if(pw==1)return g[0]=1,void();
	poly_sqrt(g,f,(pw+1)>>1);
	clr(A,pw),poly_inv(A,g,pw),poly_mul(A,f,A,pw,pw);
	for(int i=0,iv2=(mod+1)>>1;i<pw;++i)g[i]=1ll*(g[i]+A[i])*iv2%mod;
}

}
int n,f[N],g[N];
signed main(){
	n=read();
	for(int i=0;i<n;++i)f[i]=read();
	poly::poly_sqrt(g,f,n);
	for(int i=0;i<n;++i)printf("%d%c",g[i]," \n"[i==n-1]);
	return 0;
}