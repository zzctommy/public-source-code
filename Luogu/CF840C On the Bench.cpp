#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define N 305
#define mod 1000000007
void fmod(int&x){x-=mod,x+=x>>31&mod;}
int n,a[N],dp[N][N][N];
void change(int&x){
	for(int i=2;i*i<=x;++i)
		while(x%(i*i)==0)x/=i*i;
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i)change(a[i]=read());
	sort(a+1,a+n+1);
	dp[0][0][0]=1;
	for(int i=1,cnt=0;i<=n;++i){
		if(a[i]!=a[i-1]){
			for(int j=0;j<=i;++j)
				for(int k=1;k<=cnt;++k){
					fmod(dp[i-1][j][0]+=dp[i-1][j][k]);
					dp[i-1][j][k]=0;
				}
			cnt=0;
		}
		for(int j=0;j<=i;++j){
			for(int k=0,up=min(cnt,j);k<=up;++k){
				if(j&&k)fmod(dp[i][j][k]+=1ll*dp[i-1][j-1][k-1]*(cnt+cnt-k+1)%mod);
				fmod(dp[i][j][k]+=1ll*dp[i-1][j+1][k]*(j-k+1)%mod);
				fmod(dp[i][j][k]+=1ll*dp[i-1][j][k]*(i-(cnt+cnt-k)-(j-k))%mod);
			}
		}
		++cnt;
	}
	// for(int i=0;i<=n;++i){
	// 	for(int j=0;j<=n;++j){
	// 		for(int k=0;k<=n;++k)cerr<<dp[i][j][k]<<' ';
	// 		cerr<<'\n';
	// 	}
	// 	cerr<<'\n';
	// }
	printf("%d\n",dp[n][0][0]);
	return 0;
}