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
const int N=225;
const int R=140;
int n,r,d[N];
db dp[N][R],p[N],ans;
db qpow(db n,int k){db res=1;for(;k;k>>=1,n=n*n)if(k&1)res=res*n;return res;}
void Main(){
	n=read(),r=read();
	rep(i,1,n)scanf("%lf%d",&p[i],&d[i]);
	dp[1][0]=qpow(1-p[1],r),dp[1][1]=1-dp[1][0];
	rep(i,2,n)rep(j,0,min(i,r)){
		dp[i][j]=0;
		if(i!=j)dp[i][j]=dp[i-1][j]*qpow(1-p[i],r-j);
		if(j)dp[i][j]+=dp[i-1][j-1]*(1-qpow(1-p[i],r-j+1));
	}
	ans=0;
	rep(i,1,n){
		db res=0;
		if(i==1)res=1-qpow(1-p[1],r);
		else rep(j,0,min(i-1,r))res+=dp[i-1][j]*(1-qpow(1-p[i],r-j));
		ans+=res*d[i];
	}
	printf("%.10lf\n",ans);
}
signed main(){for(int T=read();T;--T)Main();}