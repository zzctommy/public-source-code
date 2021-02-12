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

LL mul(LL x,LL y,LL mod){
	LL res=x*y-(long long)((long double)x/mod*y+0.5)*mod;
	return res<0?res+mod:res;
}
LL gcd(LL x,LL y){
	while(y){LL t=x%y;x=y,y=t;}
	return x;
}
LL qpow(LL n,LL k,LL mod){
	LL res=1;for(;k;k>>=1,n=mul(n,n,mod))if(k&1)res=mul(res,n,mod);
	return res;
}

namespace MR{
int testp[8]={2,3,5,7,11,19,61,233};
bool mr(LL x,LL p){
	if(x%p==0||qpow(p,x-1,x)!=1)return 0;
	LL k=x-1;
	while(!(k&1)){
		LL t=qpow(p,k>>=1,x);
		if(t!=x-1&&t!=1)return 0;
		if(t==x-1)break;
	}
	return 1;
}
bool test(LL x){
	for(int i=0;i<8;++i){
		if(x==testp[i])return 1;
		if(!mr(x,testp[i]))return 0;
	}
	return 1;
}
}

namespace PR{
int tot;
LL d[150];
mt19937_64 rnd(673);
LL pr(LL x,LL c){
	if(x==4)return 2;
	static LL s[150],v0,v1,g;
	static int len;
	len=0,v0=c,v1=mul(v0,v0,x)+c,g=1;
	while(1){
		s[++len]=v1-v0,g=mul(g,v1-v0,x);
		if(len==127){if(gcd(g,x)>1)break;len=0;}
		v0=mul(v0,v0,x)+c,v1=mul(v1,v1,x)+c,v1=mul(v1,v1,x)+c;
	}
	for(int i=1;i<=len;++i)if((g=gcd(s[i],x))>1)return g;
	return x;
}
void solve(LL x){
	if(x==1)return;
	if(MR::test(x))return d[++tot]=x,void();
	LL y=x;while(y==x)y=pr(x,rnd()%(x-1)+1);
	solve(x/y),solve(y);
}
void work(LL x){tot=0,solve(x),sort(d+1,d+tot+1);}

}

const int N=200005;
const int M=N*3*2;
#define mod 998244353

namespace math{
int inv[N],fac[N],ifc[N];
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
inline int comb(int n,int m){return n<m?0:1ll*fac[n]*ifc[m]%mod*ifc[n-m]%mod;}
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}
void initmath(const int&n=N-1){
	fac[0]=1;for(int i=1;i<=n;++i)fac[i]=1ll*fac[i-1]*i%mod;
	ifc[n]=qpow(fac[n],mod-2);for(int i=n-1;i>=0;--i)ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
	inv[1]=1;for(int i=2;i<=n;++i)inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
}
}
using namespace math;

namespace poly{

int rev[M],rt[M],lim;
void initpoly(const int&n){
	static int lg;
	for(lg=0,lim=1;lim<n;++lg,lim<<=1);
	for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
	for(int i=1;i<lim;i<<=1){
		int w=qpow(3,(mod-1)/(i<<1));
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
				const int t=1ll*rt[i+k]*a[i+j+k]%mod;
				fmod(a[i+j+k]=a[j+k]+mod-t),fmod(a[j+k]+=t);
			}
		}
	}
	if(!op)for(int i=0,iv=qpow(lim,mod-2);i<lim;++i)a[i]=1ll*a[i]*iv%mod;
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
void bernoulli(int*g,int n){
	static int A[M];
	for(int i=0;i<n;++i)A[i]=ifc[i+1];
	clr(g,n),poly_inv(g,A,n);
}
void CZT(int*g,int*f,int m,int n,int c){//给定n-1次多项式f，求f(c^{0->m-1})
	static int pw[N<<1],ipw[N<<1],ivc,A[M],B[M];
	pw[0]=pw[1]=ipw[0]=ipw[1]=1,ivc=qpow(c,mod-2);
	for(int i=2;i<n+m;++i)pw[i]=1ll*pw[i-1]*c%mod,ipw[i]=1ll*ipw[i-1]*ivc%mod;
	for(int i=2;i<n+m;++i)pw[i]=1ll*pw[i-1]*pw[i]%mod,ipw[i]=1ll*ipw[i-1]*ipw[i]%mod;
	for(int i=0;i<n;++i)A[i]=1ll*f[i]*ipw[i]%mod;
	for(int i=0;i<n+m;++i)B[i]=pw[i];
	reverse(A,A+n),poly_mul(A,B,A,n,n+m);
	for(int i=0;i<m;++i)g[i]=1ll*ipw[i]*A[i+n-1]%mod;
}

}

using PR::d;
using PR::tot;
int m,t,a[N],A[M],B[M],tem[N],num,pri[N];
LL c;
signed main(){
	initmath();
	scanf("%d%lld%d",&m,&c,&t),++t;
	for(int i=0;i<m;++i)a[i]=read();
	if(c==1){
		static LL sum;
		sum=0;for(int i=0;i<m;++i)sum+=a[i];
		int s=sum%mod;
		for(int i=1;i<t;++i)printf("%d ",s);
		return 0;
	}
	PR::work(c);
	for(int l=1,r=0;l<=tot;l=r+1){
		while(r<tot&&d[r+1]==d[l])++r;
		pri[++num]=d[l]%mod;
	}
	A[0]=1;
	for(int i=1;i<=num;++i)A[0]=1ll*A[0]*(mod+1-(tem[i]=qpow(pri[i],mod-2)))%mod;
	for(int i=1;i<m;++i){
		A[i]=1;
		for(int j=1;j<=num;++j)A[i]=1ll*A[i]*(mod+1-(tem[j]=1ll*tem[j]*pri[j]%mod))%mod;
	}
	poly::bernoulli(B,m);
	for(int i=0;i<m;++i)A[i]=1ll*A[i]*B[i]%mod;
	for(int i=0;i<m;++i)B[i]=1ll*a[i]*fac[i]%mod;
	reverse(A,A+m),poly::poly_mul(A,B,B,m,m);
	for(int i=0;i<m;++i)A[i+1]=1ll*ifc[i+1]*B[i+m-1]%mod;
	A[0]=0,clr(B,t),poly::CZT(B,A,t,m+1,c%mod);
	for(int i=1;i<t;++i)printf("%d\n",B[i]);
	return 0;
}