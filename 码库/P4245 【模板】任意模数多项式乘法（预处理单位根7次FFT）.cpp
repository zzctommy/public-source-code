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
const int N=100005;
const int M=N<<2;
int n,m,f[M],g[M],mod;
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
namespace poly{
const db pi=acos(-1.0);
int rev[M],lg,lim;
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
}
signed main(){
	n=read(),m=read(),mod=read();
	rep(i,0,n)f[i]=read()%mod;
	rep(i,0,m)g[i]=read()%mod;
	poly::init_poly(n+m),poly::MTT(f,g,f);
	rep(i,0,n+m)printf("%d ",f[i]);
	return 0;
}