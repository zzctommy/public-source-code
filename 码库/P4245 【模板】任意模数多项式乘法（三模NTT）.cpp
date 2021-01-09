#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
const int mod[3]={469762049,998244353,1004535809};
const int N=300010;
int a[3][N],b[3][N],n,m,p,l,lim,rev[N];
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
inline LL qpow(LL n,LL k,LL P) {
	LL res=1;for(;k;k>>=1,n=n*n%P)if(k&1)res=res*n%P;
	return res;
}
inline void NTT(int *a,int P,int g) {
	for(rint i=0;i<lim;++i)
		if(i>rev[i])swap(a[i],a[rev[i]]);
	for(rint i=1;i<lim;i<<=1) {
		int wn=qpow(g,(P-1)/(i<<1),P);
		for(rint j=0;j<lim;j+=(i<<1)) {
			int w0=1;
			for(rint k=0;k<i;++k,w0=1ll*w0*wn%P) {
				int X=a[j+k],Y=1ll*w0*a[i+j+k]%P;
				a[j+k]=(X+Y)%P;
				a[i+j+k]=(X-Y+P)%P;
			}
		}
	}
}
LL get(int i) {
	LL x=a[0][i]+(a[1][i]-a[0][i]+mod[1])*qpow(mod[0],mod[1]-2,mod[1])%mod[1]*mod[0];
	return (x%p+(a[2][i]-x%mod[2]+mod[2])*qpow(1ll*mod[0]*mod[1]%mod[2],mod[2]-2,mod[2])%mod[2]*mod[0]%p*mod[1]%p)%p;
}
int main() {
	n=rd(),m=rd(),p=rd();
	for(rint i=0;i<=n;++i)a[0][i]=a[1][i]=a[2][i]=rd()%p;
	for(rint i=0;i<=m;++i)b[0][i]=b[1][i]=b[2][i]=rd()%p;
	for(lim=1,l=0;lim<=n+m;lim<<=1,++l);
	for(rint i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
	for(rint i=0;i<3;++i)NTT(a[i],mod[i],3);
	for(rint i=0;i<3;++i)NTT(b[i],mod[i],3);
	for(rint i=0;i<3;++i)
		for(rint j=0;j<lim;++j)
			a[i][j]=1ll*a[i][j]*b[i][j]%mod[i];
	for(rint i=0;i<3;++i)NTT(a[i],mod[i],qpow(3,mod[i]-2,mod[i]));
	for(rint i=0;i<3;++i) {
		int inv=qpow(lim,mod[i]-2,mod[i]);
		for(rint j=0;j<lim;++j)
			a[i][j]=1ll*inv*a[i][j]%mod[i];
	}
	for(rint i=0;i<=n+m;++i)printf("%lld%c",get(i)," \n"[i==n+m]);
	return 0;
}