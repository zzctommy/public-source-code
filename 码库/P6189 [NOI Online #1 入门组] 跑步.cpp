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
int n,mod,ans,m;
int f[N],g[320][N];
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
signed main(){
	n=read(),mod=read(),m=sqrt(n-1)+1;
	f[0]=g[0][0]=1;
	for(int i=1;i<m;++i)//每一个数都<m
		for(int j=i;j<=n;++j)
			fmod(f[j]+=f[j-i]);
	for(int i=1;i<=m;++i){//i个数>=m
		for(int j=i;j<=n;++j){
			g[i][j]=g[i][j-i];
			if(j>=m)fmod(g[i][j]+=g[i-1][j-m]);
		}
	}
	for(int i=0;i<=m;++i){
		for(int j=0;j<=n;++j)fmod(ans+=1ll*g[i][j]*f[n-j]%mod);
	}
	printf("%d\n",ans);
	return 0;
}