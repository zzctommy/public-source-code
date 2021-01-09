//Orz cyn2006
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
int dp[N<<1][N][N],n,a[N][N];
signed main(){
	memset(dp,-0x3f,sizeof(dp));
	dp[0][0][0]=0;
	n=read();
	rep(i,1,n)rep(j,1,n)a[i][j]=read();
	rep(i,1,n*2-1)rep(j,1,n){
		if(j>n||j>i||i-j+1>n)continue;
		rep(k,1,n){
			if(k>n||k>i||i-k+1>n)continue;
			int tmp;
			if(j!=k)tmp=a[j][i-j+1]+a[k][i-k+1];
			else tmp=a[j][i-j+1];
			ckmax(dp[i][j][k],dp[i-1][j][k]+tmp);
			ckmax(dp[i][j][k],dp[i-1][j-1][k]+tmp);
			ckmax(dp[i][j][k],dp[i-1][j][k-1]+tmp);
			ckmax(dp[i][j][k],dp[i-1][j-1][k-1]+tmp);
			
		}
	}
	printf("%d\n",dp[n*2-1][n][n]);
	return 0;
}