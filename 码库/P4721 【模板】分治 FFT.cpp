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
#define mod 998244353
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
int n,g[N],f[N];
namespace poly{
int lg,lim,rev[M];
void init(const int&n){
	for(lim=1,lg=0;lim<=n;lim<<=1,++lg);
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
				fmod(a[j+k]=X+Y),fmod(a[i+j+k]=X-Y+mod);
			}
		}
	}
	if(op)return;int ilim=qpow(lim,mod-2);
	for(int i=0;i<lim;++i)a[i]=1ll*a[i]*ilim%mod;
}
}
#define clr(a,n) memset(a,0,sizeof(int)*(n))
void CDQ_NTT(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	CDQ_NTT(l,mid);
	static int A[M],B[M];
	poly::init(r-l-1+mid-l),clr(A,poly::lim),clr(B,poly::lim);
	for(int i=l;i<=mid;++i)A[i-l]=f[i];
	for(int i=1;i<=r-l;++i)B[i-1]=g[i];
	poly::NTT(A,1),poly::NTT(B,1);
	for(int i=0;i<poly::lim;++i)A[i]=1ll*A[i]*B[i]%mod;
	poly::NTT(A,0);
	for(int i=mid+1;i<=r;++i)fmod(f[i]+=A[i-l-1]);
	CDQ_NTT(mid+1,r);
}
signed main(){
	n=read(),f[0]=1;rep(i,1,n-1)g[i]=read();
	CDQ_NTT(0,n-1);
	rep(i,0,n-1)printf("%d ",f[i]);
	return 0;
}