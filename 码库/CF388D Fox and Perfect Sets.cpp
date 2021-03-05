#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
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
#define mod 1000000007
inline int qpow(int n,int k){
	int res=1;
	for(;k;k>>=1,n=1ll*n*n%mod)
		if(k&1)res=1ll*n*res%mod;
	return res;
}
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}
int n,dp[35][35][2],ans;
signed main(){
	cin>>n;
	dp[30][0][1]=1;
	for(int i=30;i>=1;--i){
		for(int j=30;j>=0;--j){
			fmod(dp[i-1][j][0]+=(1ll<<j)*dp[i][j][0]%mod);
			fmod(dp[i-1][j+1][0]+=dp[i][j][0]);
			int x,y;
			if(!j)x=1,y=0;
			else x=y=1ll<<(j-1);
			if(!(n>>(i-1)&1)){
				fmod(dp[i-1][j][1]+=1ll*x*dp[i][j][1]%mod);
			}else{
				fmod(dp[i-1][j+1][1]+=dp[i][j][1]);
				fmod(dp[i-1][j][0]+=1ll*x*dp[i][j][1]%mod);
				fmod(dp[i-1][j][1]+=1ll*y*dp[i][j][1]%mod);
			}
		}
	}
	for(int i=0;i<=30;++i)fmod(ans+=dp[0][i][0]),fmod(ans+=dp[0][i][1]);
	cout<<ans<<'\n';
}