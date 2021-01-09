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
#define mod 1004535809
void fmod(int&x){x+=x>>31&mod,x-=mod,x+=x>>31&mod;}
int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
inline int exread(){
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=(1ll*x*10+ch-'0')%mod,ch=getchar();
	return x;
}

int rev[M],lg,lim;
void init(const int&n){
	for(lg=0,lim=1;lim<=n;lim<<=1,++lg);
	for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
}
void NTT(int*a,int op){
	int g=op?3:qpow(3,mod-2);
	for(int i=0;i<lim;++i)if(i>rev[i])swap(a[i],a[rev[i]]);
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
	for(int i=0;i<lim;++i)a[i]=1ll*ilim*a[i]%mod;
}

int n,k,t,a[M],f[M];
namespace solve1{
signed main(){
	f[0]=1;for(int i=1;i<n;++i)f[i]=1ll*f[i-1]*(k+i-1)%mod*qpow(i,mod-2)%mod;
	init(n<<1),NTT(a,1),NTT(f,1);
	for(int i=0;i<lim;++i)f[i]=1ll*a[i]*f[i]%mod;
	NTT(f,0);
	for(int i=0;i<n;++i)fmod(f[i]),printf("%d ",f[i]);
	return 0;
}

}
namespace solve2{
signed main(){
	f[0]=1;for(int i=1;i<n;++i)f[i]=-1ll*f[i-1]*(k-i+1)%mod*qpow(i,mod-2)%mod;
	init(n<<1),NTT(a,1),NTT(f,1);
	for(int i=0;i<lim;++i)f[i]=1ll*a[i]*f[i]%mod;
	NTT(f,0);
	for(int i=0;i<n;++i)fmod(f[i]),printf("%d ",f[i]);
	return 0;
}
}
signed main(){
	n=read(),k=exread(),t=read();
	for(int i=0;i<n;++i)a[i]=read();
	if(!t)solve1::main();else solve2::main();
	return 0;
}