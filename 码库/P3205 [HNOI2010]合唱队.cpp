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
const int N=1005;
const int mod=19650827;
int dp[N][N][2],n,a[N],ans;
void fmod(int&x){
	x+=x>>31&mod,x-=mod,x+=x>>31&mod;
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i)a[i]=read(),dp[i][i][0]=1;
	for(int len=2;len<=n;++len){
		for(int l=1;;++l){
			int r=l+len-1;
			if(r>n)break;
			if(a[l]<a[l+1])fmod(dp[l][r][0]+=dp[l+1][r][0]);
			if(a[l]<a[r])fmod(dp[l][r][0]+=dp[l+1][r][1]);
			if(a[r]>a[r-1])fmod(dp[l][r][1]+=dp[l][r-1][1]);
			if(a[r]>a[l])fmod(dp[l][r][1]+=dp[l][r-1][0]);
		}
	}
	fmod(ans=dp[1][n][0]+dp[1][n][1]),printf("%d\n",ans);
	return 0;
}