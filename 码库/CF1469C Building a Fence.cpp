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
#define int long long
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=200005;
int n,k,h[N],dp[N][2];
void Main(){
	n=read(),k=read();
	rep(i,1,n)h[i]=read();
	dp[1][0]=h[1],dp[1][1]=h[1];
	for(int i=2;i<=n;++i){
		dp[i][0]=max(h[i],dp[i-1][0]-k+1);
		dp[i][1]=min(h[i]+k-1,dp[i-1][1]+k-1);
		if(dp[i][0]>dp[i][1])return puts("NO"),void();
	}
	if(dp[n][0]!=h[n])puts("NO");
	else puts("YES");
}
signed main(){for(int T=read();T;--T)Main();}//???UKE???