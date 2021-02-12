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
const int N=305;
#define mod1 998244353
#define mod2 1000000007
#define base1 31
#define base2 37
int n,m,H1[N][N],H2[N][N],pw1[N],pw2[N];
db a[N][N],ans[N],pw[N];
int hash1(int id,int l,int r){
	return (H1[id][r]-1ll*H1[id][l-1]*pw1[r-l+1]%mod1+mod1)%mod1;
}
int hash2(int id,int l,int r){
	return (H2[id][r]-1ll*H2[id][l-1]*pw2[r-l+1]%mod2+mod2)%mod2;
}
void Gauss(int n){
	rep(i,1,n){
		int mx=i;
		rep(j,i,n)if(fabs(a[j][i])>fabs(a[mx][i]))mx=j;
		if(mx!=i)rep(j,1,n+1)swap(a[mx][j],a[i][j]);
		rep(j,1,n){
			if(i==j)continue;
			db div=a[j][i]/a[i][i];
			rep(k,i,n+1)a[j][k]-=a[i][k]*div;
		}
	}
	rep(i,1,n)ans[i]=a[i][n+1]/a[i][i];
}
signed main(){
	n=read(),m=read();
	pw[0]=pw1[0]=pw2[0]=1;
	rep(i,1,m)pw1[i]=1ll*pw1[i-1]*base1%mod1,pw2[i]=1ll*pw2[i-1]*base2%mod2,pw[i]=2.*pw[i-1];
	rep(i,1,n){
		static char str[N];scanf("%s",str+1);
		rep(j,1,m)H1[i][j]=(1ll*H1[i][j-1]*base1+(str[j]=='H')+1)%mod1,H2[i][j]=(1ll*H2[i][j-1]*base2+(str[j]=='H')+1)%mod2;
	}
	rep(i,1,n){
		db res=0;
		rep(j,1,n)rep(k,1,m)
			if(hash1(i,1,k)==hash1(j,m-k+1,m)&&hash2(i,1,k)==hash2(j,m-k+1,m))a[i][j]+=pw[k];
		a[i][n+1]=-1,a[i][n+2]=0;
	}
	rep(i,1,n)a[n+1][i]=1;a[n+1][n+1]=0,a[n+1][n+2]=1;
	Gauss(n+1);
	for(int i=1;i<=n;++i)printf("%.10lf\n",ans[i]);
	return 0;
}