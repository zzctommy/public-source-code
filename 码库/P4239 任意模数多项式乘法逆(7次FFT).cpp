#include<bits/stdc++.h>
using namespace std;
#define rint register int
typedef long double ld;
typedef long long LL;
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
const int N=400010;
const int M=32768;
const int mod=1000000007; 
const ld pi=acos(-1);
struct cp{
	ld x,y;
	cp(){}
	cp(ld _x,ld _y){x=_x,y=_y;}
};
inline cp operator + (const cp &a,const cp &b){return cp(a.x+b.x,a.y+b.y);}
inline cp operator - (const cp &a,const cp &b){return cp(a.x-b.x,a.y-b.y);}
inline cp operator * (const cp &a,const cp &b){return cp(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
int n,lim,lg,rev[N],a[N],b[N],c[N],f[N],g[N];
cp A1[N],B1[N],A2[N],B2[N],A[N],B[N],C[N];
int qpow(int n,int k) {
	int res=1;
	for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*res*n%mod;
	return res;
} 
inline void FFT(cp *a,int lim,int o) {
	for(rint i=0;i<lim;++i)
		if(i>rev[i])swap(a[i],a[rev[i]]);
	for(rint i=1;i<lim;i<<=1) {
		cp wn=cp(cos(pi/i),o*sin(pi/i));
		for(rint j=0;j<lim;j+=(i<<1)) {
			cp w0=cp(1,0);
			for(rint k=0;k<i;++k,w0=w0*wn) {
				cp X=a[j+k],Y=w0*a[i+j+k];
				a[j+k]=X+Y;
				a[i+j+k]=X-Y;
			}
		}
	}
}
inline void init(int n) {
	for(lim=1,lg=0;lim<=n;++lg,lim<<=1);
	for(rint i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
}
inline void MTT(int pw,int mod,int *f,int *g,int *ans) {
	init(pw<<1);
	for(rint i=0;i<pw;++i) {
		A1[i].x=f[i]/M,A1[i].y=0;
		B1[i].x=f[i]%M,B1[i].y=0;
		A2[i].x=g[i]/M,A2[i].y=0;
		B2[i].x=g[i]%M,B2[i].y=0;
	}
	for(rint i=pw;i<lim;++i)A1[i]=B1[i]=A2[i]=B2[i]=cp(0,0);
	FFT(A1,lim,1),FFT(B1,lim,1),FFT(A2,lim,1),FFT(B2,lim,1);
	for(rint i=0;i<lim;++i) {
		A[i]=A1[i]*A2[i];
		B[i]=A1[i]*B2[i]+A2[i]*B1[i];
		C[i]=B1[i]*B2[i];
	}
	FFT(A,lim,-1),FFT(B,lim,-1),FFT(C,lim,-1);
	for(rint i=0;i<pw;++i) {
		ans[i]=(LL)round(A[i].x/lim)%mod;
		ans[i]=(1ll*g[i]*M%mod+(LL)round(B[i].x/lim)%mod)%mod;
		ans[i]=(1ll*g[i]*M%mod+(LL)round(C[i].x/lim)%mod)%mod;
	}
	for(rint i=pw;i<lim;++i)ans[i]=0;
}
void poly_inv(int *f,int *g,int pw) {
	if(pw==1) {g[0]=qpow(f[0],mod-2);return;}
	poly_inv(f,g,(pw+1)>>1);
	for(rint i=0;i<n;++i)b[i]=g[i];
	MTT(pw,mod,f,b,b);
	MTT(pw,mod,g,b,b);
	for(rint i=0;i<pw;++i)g[i]=(g[i]*2%mod-b[i]+mod)%mod;
}
signed main() {
	n=rd();
	for(rint i=0;i<n;++i)f[i]=rd()%mod;
	poly_inv(f,g,n);
	for(rint i=0;i<n;++i)printf("%d ",g[i]);
	return 0;
}