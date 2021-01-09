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
#define mod 998244353
const int N=10000005;
int n,k,p,ans;
int f[N];

namespace math{
int id[N],pct,inv[N];
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}
void initmath(const int&n=N-1){
	id[1]=1,id[0]=0;
	for(int i=2;i<=n;++i){
		if(!inv[i])f[++pct]=i,id[i]=qpow(i,k);
		for(int j=1;i*f[j]<=n&&j<=pct;++j){
			inv[i*f[j]]=1,id[i*f[j]]=1ll*id[i]*id[f[j]]%mod;
			if(i%f[j]==0)break;
		}
	}
	inv[1]=1;for(int i=2;i<=n;++i)inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
}

}
using namespace math;

namespace solve1{
void main(){
	f[0]=1;for(int i=1;i<=n;++i)f[i]=1ll*(mod+1-p)*f[i-1]%mod;
	for(int i=0,j=1,y=1;i<=n;++i){
		fmod(ans+=1ll*j*y%mod*f[n-i]%mod*id[i]%mod);
		j=1ll*j*(n-i)%mod*inv[i+1]%mod,y=1ll*y*p%mod;
	}
	printf("%d\n",ans),exit(0);
}

}

namespace solve2{
void main(){
	f[k]=1;
	for(int i=k-1,x=0,z=1,y=1;i>=0;--i){
		++x,z=1ll*z*(x+n-k-1)%mod*inv[x]%mod,y=1ll*y*(mod-p)%mod;
		fmod(f[i]=1ll*(mod+1-p)*f[i+1]%mod),fmod(f[i]+=1ll*y*z%mod);
	}
	for(int i=0,j=1,y=1;i<=k;++i){
		fmod(ans+=1ll*id[i]*j%mod*y%mod*f[i]%mod);
		j=1ll*j*(n-i)%mod*inv[i+1]%mod,y=1ll*y*p%mod;
	}
	printf("%d\n",ans),exit(0);
}

}


signed main(){
	n=read(),p=qpow(read(),mod-2),k=read(),initmath(min(n,k)+3);
	if(n<=k)solve1::main();
	else solve2::main();
}