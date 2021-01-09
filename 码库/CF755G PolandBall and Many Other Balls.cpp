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
const int N=1<<15;
const int M=N<<2;
int n,k,f[3][M];
namespace poly{
#define mod 998244353
int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
void fmod(int&x){x-=mod,x+=x>>31&mod;}
int rev[M],lg,lim;
void init_poly(const int&n){
	for(lg=0,lim=1;lim<=n;lim<<=1,++lg);
	for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
}
void NTT(int*a,int op){
	for(int i=0;i<lim;++i)if(i>rev[i])swap(a[i],a[rev[i]]);
	int g=op?3:qpow(3,mod-2);
	for(int i=1;i<lim;i<<=1){
		int wn=qpow(g,(mod-1)/(i<<1));
		for(int j=0;j<lim;j+=i<<1){
			int w0=1;
			for(int k=0;k<i;++k,w0=1ll*w0*wn%mod){
				const int X=a[j+k],Y=1ll*w0*a[i+j+k]%mod;
				a[j+k]=(X+Y)%mod,a[i+j+k]=(X-Y+mod)%mod;
			}
		}
	}
	if(op)return;int ilim=qpow(lim,mod-2);
	for(int i=0;i<lim;++i)a[i]=1ll*ilim*a[i]%mod;
}
#define clr(a,n) memset(a,0,sizeof(int)*(n))
#define cpy(a,b,n) memcpy(a,b,sizeof(int)*(n))
void mul(const int&n){
	static int A[M],B[M],C[M],D[M],E[M];
	NTT(f[0],1),NTT(f[1],1),NTT(f[2],1);
	for(int i=0;i<lim;++i)
		A[i]=1ll*f[0][i]*f[0][i]%mod,
		B[i]=1ll*f[1][i]*f[1][i]%mod,
		C[i]=1ll*f[0][i]*f[1][i]%mod,
		D[i]=1ll*f[2][i]*f[1][i]%mod,
		E[i]=1ll*f[2][i]*f[2][i]%mod;
	NTT(A,0),NTT(B,0),NTT(C,0),NTT(D,0),NTT(E,0);
	clr(f[0],lim),clr(f[1],lim),clr(f[2],lim);
	for(int i=0;i<=n;++i)
		fmod(f[0][i]=A[i]+(i?B[i-1]:0)),
		fmod(f[1][i]=C[i]+(i?D[i-1]:0)),
		fmod(f[2][i]=B[i]+(i?E[i-1]:0));
}
void add(const int&n){
	cpy(f[2],f[1],n+1),cpy(f[1],f[0],n+1),f[0][0]=1;
	for(int i=1;i<=n;++i)f[0][i]=((f[1][i]+f[1][i-1])%mod+f[2][i-1])%mod;
}

}


signed main(){
	n=read(),k=read();
	f[1][0]=1;
	f[0][0]=f[0][1]=1;
	poly::init_poly(k<<1);
	for(int i=log2(n)-1;i>=0;--i){
		poly::mul(k);
		if(n>>i&1)poly::add(k);
	}
	for(int i=1;i<=k;++i)printf("%d ",f[0][i]);puts("");
	return 0;
}