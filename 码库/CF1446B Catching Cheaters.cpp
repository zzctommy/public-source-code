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
const int N=5005;
int dp[N][N],n,m,ans;
char S[N],T[N];
signed main(){
	scanf("%d%d%s%s",&n,&m,S+1,T+1);
	dp[0][0]=0;
	rep(i,1,n)rep(j,1,m){
		if(S[i]==T[j])dp[i][j]=dp[i-1][j-1]+2;
		ckmax(dp[i][j],max(dp[i][j-1]-1,dp[i-1][j]-1));
		ckmax(ans,dp[i][j]);
	}
	cout<<ans<<'\n';
}