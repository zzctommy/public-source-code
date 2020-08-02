#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=300010;
const int mod=998244353;
const int P=1e9+7;
int qpow(int n,int k,int p=mod) {
	int res=1;
	while(k) {
		if(k&1)res=1ll*res*n%p;
		n=1ll*n*n%p,k>>=1;
	}
	return res;
}
const int G=3;
const int IG=qpow(G,mod-2);
int A[N],B[N],n,ans,C[N];
char s[N],t[N];
int lim,lg,rev[N];
int hw[N],m;
void init(int n) {
	for(lim=1,lg=0;lim<n;lim<<=1,++lg);
	for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
}
void NTT(int*a,int g,int op=0) {
	for(int i=0;i<lim;++i)
		if(i>rev[i])swap(a[i],a[rev[i]]);
	for(int i=1;i<lim;i<<=1) {
		int wn=qpow(g,(mod-1)/(i<<1));
		for(int j=0;j<lim;j+=(i<<1)) {
			int w0=1;
			for(int k=0;k<i;++k,w0=1ll*w0*wn%mod) {
				int X=a[j+k],Y=1ll*w0*a[i+j+k]%mod;
				a[j+k]=(X+Y)%mod,a[i+j+k]=(X-Y+mod)%mod;
			}
		}
	}
	if(!op)return;int ilim=qpow(lim,mod-2);
	for(int i=0;i<lim;++i)a[i]=1ll*a[i]*ilim%mod;
}
void change() {
	t[m++]='~',t[m++]='|';
	for(int i=0;i<n;++i)t[m++]=s[i],t[m++]='|';
	t[m++]=0;
}
void manacher() {
	change();
	int mxr=0,mid=0,sum=0;
	for(int i=0;i<m;++i) {
		if(i<mxr)hw[i]=min(mxr-i,hw[(mid<<1)-i]);
		while(t[i+hw[i]]==t[i-hw[i]])++hw[i];
		if(i+hw[i]>mxr)mxr=i+hw[i],mid=i;
		sum=(sum+(hw[i]>>1))%P;
	}
	ans=(ans-sum)%P;
}
signed main() {
	scanf("%s",s),n=strlen(s);
	for(int i=0;i<n;++i)A[i]=s[i]=='a',B[i]=s[i]=='b';
	init(n<<1),NTT(A,G),NTT(B,G);
	for(int i=0;i<lim;++i)A[i]=1ll*A[i]*A[i]%mod,B[i]=1ll*B[i]*B[i]%mod;
	NTT(A,IG,1),NTT(B,IG,1);
	for(int i=0;i<lim;++i)C[i]=((A[i]+1)>>1)+((B[i]+1)>>1);
	for(int i=0;i<lim;++i)ans=(ans+qpow(2,C[i],P)-1)%P;
	manacher();
	printf("%d\n",(ans%P+P)%P);
	return 0;
}
