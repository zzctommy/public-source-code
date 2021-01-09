#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef long double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return x;
}
int rdc(){
	char ch=getchar();
	while(ch!='#'&&ch!='.')ch=getchar();
	return ch=='#';
}
#define mod 1000000007
void fmod(int&x){x+=x>>31&mod,x-=mod,x+=x>>31&mod;}
const int N=1005;
int n,m,a[N][N];
int cnt,cnt1,cnt2,x,y,ans;
LL k;
int qpow(int n,LL k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*res*n%mod;return res;}
struct Matrix{
	int a[2][2];
	Matrix(){a[0][0]=a[0][1]=a[1][0]=a[1][1]=0;}
	int*operator [] (const int&k){return a[k];}
	friend Matrix operator * (const Matrix&a,const Matrix&b){
		Matrix res;
		rep(i,0,1)rep(j,0,1)rep(k,0,1)fmod(res.a[i][j]+=1ll*a.a[i][k]*b.a[k][j]%mod);
		return res;
	}
	void e(){
		a[0][0]=1,a[0][1]=0;
		a[1][0]=0,a[1][1]=1;
	}
}sta,tur;
Matrix Matrix_pow(Matrix a,LL k){
	Matrix res;res.e();
	for(;k;k>>=1,a=a*a)if(k&1)res=res*a;
	return res;
}
int solve(int x,int y,int z,LL k){
	sta[0][0]=1,sta[0][1]=y;
	tur[0][0]=x,tur[0][1]=0;
	tur[1][0]=-1,tur[1][1]=z;
	tur=Matrix_pow(tur,k);
	sta=sta*tur;
	return sta[0][0];
}
signed main(){
	scanf("%d%d%lld",&n,&m,&k);
	rep(i,1,n)rep(j,1,m)a[i][j]=rdc(),cnt+=a[i][j];
	rep(i,1,n)rep(j,1,m-1)cnt1+=a[i][j]&&a[i][j+1];//左右连边
	rep(i,1,n-1)rep(j,1,m)cnt2+=a[i][j]&&a[i+1][j];//上下连边
	rep(i,1,n)x+=a[i][1]&&a[i][m];//左右是否联通
	rep(j,1,m)y+=a[n][j]&&a[1][j];//上下是否联通
	if(x&&y)return puts("1"),0;
	if(!x&&!y)return printf("%d\n",qpow(cnt,k-1)),0;
	if(x&&!y)return printf("%d\n",solve(cnt,cnt1,x,k-1)),0;
	if(y&&!x)return printf("%d\n",solve(cnt,cnt2,y,k-1)),0;
	return 0;
}