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
const int N=105;
#define mod 9999973
int n,m,dp[N][N][N],ans;
void fmod(int&x){x-=mod,x+=x>>31&mod;}
signed main(){
	n=read(),m=read();
	dp[0][m][0]=1;
	rep(i,0,n-1){
		rep(j,0,m){
			rep(k,0,m){
				fmod(dp[i+1][j][k]+=dp[i][j][k]);//0
				if(j>0)fmod(dp[i+1][j-1][k+1]+=1ll*j*dp[i][j][k]%mod);//1
				if(k>0)fmod(dp[i+1][j][k-1]+=1ll*k*dp[i][j][k]%mod);//1
				if(j>1)fmod(dp[i+1][j-2][k+2]+=1ll*j*(j-1)/2*dp[i][j][k]%mod);//2
				if(k>1)fmod(dp[i+1][j][k-2]+=1ll*k*(k-1)/2*dp[i][j][k]%mod);//2
				if(j>0&&k>0)fmod(dp[i+1][j-1][k]+=1ll*j*k*dp[i][j][k]%mod);//2
			}
		}
	}
	rep(i,0,m)rep(j,0,m)fmod(ans+=dp[n][i][j]);
	printf("%d\n",ans);
	return 0;
}