#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?x:-x;
}
const int N=2005;
const int mod=1e5+3;
int a,b,c,d,k,dp[N][N];
signed main(){
	a=read(),b=read(),c=read(),d=read(),k=read();
	for(int i=1;i<=b+d;++i)dp[i][0]=1;
	dp[0][0]=1;
	for(int i=1;i<=b+d;++i){
		int l=i<=b?a:a+c;
		for(int j=1;j<=k;++j)dp[i][j]=(dp[i-1][j]+1ll*dp[i-1][j-1]*(l-j+1)%mod)%mod;
	}
	printf("%d\n",dp[d+b][k]);
	return 0;
}