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

const int N=2000005;
const int M=N<<2;
#define mod 998244353
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}

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
void CZT(int*g,int*f,int m,int n,int c){//给定n次多项式f，求f(c^{0->m-1})
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

int n,c,m,a[N],A[M],B[M],pw[N],ipw[N];
signed main(){
	n=read(),c=read(),m=read();
	for(int i=0;i<n;++i)a[i]=read();
	poly::CZT(B,a,m,n,c);
	for(int i=0;i<m;++i)printf("%d ",B[i]);
	return 0;
}