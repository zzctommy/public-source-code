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
const int N=1005;
int n,k,m,x[N],y[N],ans,ivm;
namespace math{
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}
}
using math::qpow;
using math::fmod;

struct Matrix{
	int a[2][2];
	Matrix(){memset(a,0,sizeof(a));}
	Matrix operator * (const Matrix&t){
		Matrix res;
		// rep(i,0,1)rep(j,0,1)rep(k,0,1)fmod(res.a[i][j]+=1ll*a[i][k]*t.a[k][j]%mod);
		fmod(res.a[0][0]+=1ll*a[0][0]*t.a[0][0]%mod),fmod(res.a[0][0]+=1ll*a[0][1]*t.a[1][0]%mod);
		fmod(res.a[0][1]+=1ll*a[0][0]*t.a[0][1]%mod),fmod(res.a[0][1]+=1ll*a[0][1]*t.a[1][1]%mod);
		fmod(res.a[1][0]+=1ll*a[1][0]*t.a[0][0]%mod),fmod(res.a[1][0]+=1ll*a[1][1]*t.a[1][0]%mod);
		fmod(res.a[1][1]+=1ll*a[1][0]*t.a[0][1]%mod),fmod(res.a[1][1]+=1ll*a[1][1]*t.a[1][1]%mod);
		return res;
	}
	void e(){a[0][0]=a[1][1]=1,a[1][0]=a[0][1]=0;}
};
Matrix Matrix_qpow(Matrix a,int k){
	Matrix res;res.e();
	for(;k;k>>=1,a=a*a)if(k&1)res=res*a;
	return res;
}

int calc(int yx,int zs,int k){
	int tmp=1ll*yx*zs%mod*ivm%mod;
	Matrix tur,sta;
	sta.a[0][0]=tmp;
	tur.a[0][0]=mod+2-tmp*2%mod,tur.a[0][1]=1;
	tur.a[1][0]=(tmp*2-1)%mod,tur.a[1][1]=0;
	sta=sta*Matrix_qpow(tur,k-1);
	// for(int i=2;i<=k;++i)res=(1ll*(mod+1-tmp*2%mod)*res%mod+tmp)%mod;
	// return res;
	return sta.a[0][0];
}
signed main(){
	n=read(),m=read(),k=read(),ivm=qpow(1ll*(m*m)*(m*m-m*2+1)/4%mod,mod-2);
	for(int i=1;i<=m;++i)x[i]=read();
	for(int i=1;i<=m;++i)y[i]=read();
	for(int i=1;i<=m;++i)
		for(int j=1;j<=m;++j){
			int num=1ll*(x[i]-x[i-1])*(y[j]-y[j-1])%mod;
			int tmp=calc((m-i+1)*(m-j+1),(i-1)*(j-1),k);
			fmod(ans+=1ll*num*tmp%mod);
		}
	cout<<ans<<'\n';
	return 0;
}