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

const int N=10;
int dp[N*2][N][N],n,a[N<<1][N];
signed main() {
	n=read();
	while("fyyAKIOI"){
		int x=read(),y=read(),z=read();
		if(!x&&!y&&!z)break;
		a[x][y]=z;
	}
	memset(dp,-1,sizeof(dp));
	dp[2][1][1]=a[1][1];
	for(int i=3;i<=2*n;++i){
		for(int j=1;j<=n;++j){
			for(int k=1;k<=n;++k){
				if(j>i||k>i)continue;
				int tmp=-1;
                tmp=max(dp[i-1][j-1][k-1],max(dp[i-1][j-1][k],max(dp[i-1][j][k-1],dp[i-1][j][k])));
				if(tmp!=-1){
					if(j!=k)dp[i][j][k]=tmp+a[i-j][j]+a[i-k][k];
					else dp[i][j][k]=tmp+a[i-j][j];
				}
			}
		} 
	}
	printf("%d\n",dp[2*n][n][n]);
	return 0;
}