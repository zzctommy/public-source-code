#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define int long long
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int mod=998244353;
const int N=300010;
int n,l,c;
int A[N],B[N];
int jc[N],jv[N];
int lim,lg,rev[N];
int qpow(int n,int k) {
	int res=1;k=(k+mod-1)%(mod-1);
	for(;k;k>>=1,n=n*n%mod)if(k&1)res=res*n%mod;
	return res;
}
int inv(int x) {if(x<0)x+=mod;return qpow(x%mod,mod-2);}
void prework() {
	jc[0]=1;
	for(int i=1;i<=n;++i)jc[i]=jc[i-1]*i%mod;
	jv[n]=inv(jc[n]);
	for(int i=n-1;i>=0;--i)jv[i]=jv[i+1]*(i+1)%mod;
}
void init(int n) {
	for(lim=1,lg=0;lim<=n;lim<<=1,++lg);
	for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
}
void NTT(int *a,int g) {
	for(int i=0;i<lim;++i)
		if(i>rev[i])swap(a[i],a[rev[i]]);
	for(int i=1;i<lim;i<<=1) {
		int wn=qpow(g,(mod-1)/(i<<1));
		for(int j=0;j<lim;j+=(i<<1)) {
			int w0=1;
			for(int k=0;k<i;++k,w0=w0*wn%mod) {
				int X=a[j+k],Y=w0*a[i+j+k]%mod;
				a[j+k]=(X+Y)%mod;
				a[i+j+k]=(X-Y+mod)%mod;
			}
		}
	}
}
int f(int a1,int n,int q) {
	if(q==0)return 0;
	if(q==1)return n;
	return (((a1-a1*qpow(q,n)%mod+mod)%mod)*inv(1-q))%mod;
}
signed main() {
	n=rd(),l=rd(),c=rd();
	if(n==1)return printf("%lld\n",l%mod),0;
	prework();
	for(int i=0,j=1;i<=n;++i,j*=-1)A[i]=(j*f(qpow(c,1-i),l,qpow(c,1-i))*jv[i]%mod+mod)%mod;
	for(int i=0;i<=n;++i)B[i]=jv[i];
	init(n<<1|1);
	NTT(A,3),NTT(B,3);
	for(int i=0;i<lim;++i)A[i]=A[i]*B[i]%mod;
	NTT(A,inv(3));
	for(int i=0,lv=inv(lim);i<lim;++i)A[i]=A[i]*lv%mod;
	int total=f(c%mod,l,c%mod);
	for(int i=1;i<=n;++i)
		A[i]=(total-A[i]*jc[i]%mod+mod)%mod;
	for(int i=1;i<=n;++i)printf("%lld\n",A[i]);
	return 0;
}
