#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100005;
int T,mod,A,B,C,iv6;
int mu[N],pri[N/9],cnt,jc[N],jp[N],sm[N],jk[N],st[N],phi[N],fp[N],vf[N];
bool vis[N];
int qpow(int n,int k,int res=1){
	for(;k;k>>=1,n=1ll*n*n%mod)
		if(k&1)res=1ll*n*res%mod;
	return res;
}
void Sieve(const int N=100000){
	mu[1]=1,phi[1]=1,jc[0]=1,jp[0]=1,jk[0]=1,st[0]=1,fp[0]=1,fp[1]=1,vf[0]=1;
	for(int i=2;i<=N;++i){
		fp[i]=1;
		if(!vis[i])pri[++cnt]=i,mu[i]=-1,phi[i]=i-1;
		for(int j=1;j<=cnt&&i*pri[j]<=N;++j){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0){phi[i*pri[j]]=phi[i]*pri[j];break;}
			mu[i*pri[j]]=-mu[i],phi[i*pri[j]]=phi[i]*phi[pri[j]];
		}
	}
	for(int i=1;i<=N;++i){
		if(!mu[i])continue;
		for(int j=1;i*j<=N;++j)
			if(mu[i]==1)fp[i*j]=1ll*fp[i*j]*j%mod;
			else fp[i*j]=1ll*fp[i*j]*qpow(j,mod-2)%mod;
	}
	for(int i=1;i<=N;++i)fp[i]=1ll*fp[i]*fp[i-1]%mod,vf[i]=qpow(fp[i],mod-2);
	for(int i=1;i<=N;++i)
		jc[i]=1ll*jc[i-1]*i%mod,
		jp[i]=1ll*jp[i-1]*qpow(i,i)%mod,
		sm[i]=(sm[i-1]+1ll*mu[i]*i%(mod-1)*i%(mod-1))%(mod-1),
		jk[i]=1ll*jk[i-1]*qpow(i,1ll*i*i%(mod-1))%mod,
		mu[i]+=mu[i-1],
		st[i]=1ll*st[i-1]*qpow(i,phi[i])%mod,
		phi[i]=(phi[i]+phi[i-1])%(mod-1);
/*
	Attention:
	mu:∑μ
	jc :阶乘 mod mod
	jp : i^i 的前缀积 mod mod
	sm：∑μ(x)*x*x mod (mod-1)
	jk:∏i^(i^2) mod (mod-1)
	phi:∑φ mod (mod-1)
	st:πT^phi(T) mod mod
	fp:∑π(d|T)d^μ(T/d) mod mod
	vf:qpow(fp,mod-2)
*/
}
namespace Task0{
	int fz,fm;
	int f(int n,int m){
		if(n>m)n^=m^=n^=m;
		int res=0;
		for(int l=1,r;l<=n;l=r+1)
			r=min(n/(n/l),m/(m/l)),res=(res+1ll*(n/l)*(m/l)%(mod-1)*(mu[r]-mu[l-1])%(mod-1))%(mod-1);
		return (res+mod-1)%(mod-1);
	}
	int g(int n,int m){
		if(n>m)n^=m^=n^=m;
		int res=1;
		for(int l=1,r;l<=n;l=r+1)
			r=min(n/(n/l),m/(m/l)),res=1ll*res*qpow(1ll*jc[r]*qpow(jc[l-1],mod-2)%mod,f(n/l,m/l))%mod;
		return (res+mod)%mod;
	}
	void main(){
		fz=qpow(1ll*qpow(jc[A],B)*qpow(jc[B],A)%mod,C)%mod;
		fm=qpow(1ll*qpow(g(A,B),C)*qpow(g(A,C),B)%mod,mod-2);
		printf("%lld ",1ll*fz*fm%mod);
	}
}
namespace Task1{
	int fz,fm;
	int s(int x,int y){
		return (1ll*x*(x+1)/2%(mod-1))*(1ll*y*(y+1)/2%(mod-1))%(mod-1);
	}
	int s2(int x){
		return 1ll*x*(x+1)%mod*(x+x+1)%mod*iv6%mod;
	}
	int f(int n,int m){
		if(n>m)n^=m^=n^=m;
		int res=0;
		for(int l=1,r;l<=n;l=r+1){
			r=min(n/(n/l),m/(m/l));
			res=(res+1ll*s(n/l,m/l)*(sm[r]-sm[l-1])%(mod-1))%(mod-1);
		}
		return (res+mod-1)%(mod-1);
	}
	int g(int n,int m){
		if(n>m)n^=m^=n^=m;
		int res=1;
		for(int l=1,r;l<=n;l=r+1){
			r=min(n/(n/l),m/(m/l));
			res=1ll*res*qpow(1ll*jk[r]*qpow(jk[l-1],mod-2)%mod,f(n/l,m/l))%mod;
		}
		return (res+mod)%mod;
	}
	void main(){
		fz=qpow(1ll*qpow(jp[A],1ll*B*(B+1)/2%(mod-1))*qpow(jp[B],1ll*A*(A+1)/2%(mod-1))%mod,1ll*C*(C+1)/2%(mod-1));
		fm=qpow(1ll*qpow(g(A,B),1ll*C*(C+1)/2%(mod-1))*qpow(g(A,C),1ll*B*(B+1)/2%(mod-1))%mod,mod-2);
		printf("%lld ",1ll*fz*fm%mod);
	}
}
namespace Task2{
	int fz,fm;
	int f(int A,int B,int C){
		int res=1;
		for(int l=1,r,mx=min(A,min(B,C));l<=mx;l=r+1){
			r=min(A/(A/l),min(B/(B/l),C/(C/l)));
			res=1ll*res*qpow(jc[A/l],1ll*(B/l)*(C/l)%(mod-1)*(phi[r]-phi[l-1]+mod-1)%(mod-1))%mod;
			res=1ll*res*qpow(1ll*st[r]*qpow(st[l-1],mod-2)%mod,1ll*(A/l)*(B/l)*(C/l)%(mod-1))%mod;
		}
		return res;
	}
	int h(int n,int m){
		if(n>m)n^=m^=n^=m;
		int res=1;
		for(int l=1,r;l<=n;l=r+1){
			r=min(n/(n/l),m/(m/l));
			res=1ll*res*qpow(1ll*fp[r]*vf[l-1]%mod,1ll*(n/l)*(m/l)%(mod-1))%mod;
		}
		return res;
	}
	int g(int A,int B,int C){
		int res=1;
		for(int l=1,r,mx=min(A,min(B,C));l<=mx;l=r+1){
			r=min(A/(A/l),min(B/(B/l),C/(C/l)));
			res=1ll*res*qpow(1ll*st[r]*qpow(st[l-1],mod-2)%mod,1ll*(A/l)*(B/l)*(C/l)%(mod-1))%mod;
			res=1ll*res*qpow(h(A/l,B/l),1ll*(phi[r]-phi[l-1]+mod-1)*(C/l)%(mod-1))%mod;
		}
		return res;
	} 
	void main(){
		fz=1ll*f(A,B,C)*f(B,A,C)%mod;
		fm=qpow(1ll*g(A,B,C)*g(A,C,B)%mod,mod-2);
		printf("%lld ",1ll*fz*fm%mod);
	}
}

signed main(){
	T=read(),mod=read(),iv6=qpow(6,mod-2),Sieve();
	while(T--) {
		A=read(),B=read(),C=read();
		Task0::main(),Task1::main(),Task2::main(),puts("");
	}
}
/*
3 998244353
6 6 6
100000 100000 100000
99998 99999 100000

570465346 682784945 524427235
862376103 371412326 358248208
103815203 127873959 745848036
*/