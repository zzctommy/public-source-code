// Problem: C. Colorful Bricks
// Contest: Codeforces - Avito Cool Challenge 2018
// URL: https://codeforces.com/contest/1081/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms

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
const int N=2005;
#define mod 998244353
int dp[N][N],n,m,k;
signed main(){
	n=read(),m=read(),k=read();
	dp[1][0]=m;
	rep(i,2,n){
		rep(j,0,min(i-1,k)){
			dp[i][j]=(dp[i-1][j]+1ll*dp[i-1][j-1]*(m-1)%mod)%mod;
		}
	}
	printf("%d\n",dp[n][k]);
	return 0;
}