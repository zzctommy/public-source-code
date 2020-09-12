#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=3009;
const int inf=0x3f3f3f3f;
int n,s[N],c[N],dp[N][2],ans=1e15;
signed main() {
	n=rd();
	for(int i=1;i<=n;++i)s[i]=rd();
	for(int i=1;i<=n;++i)c[i]=rd();
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n;++i) {
		for(int j=1;j<i;++j)if(s[j]<s[i])dp[i][0]=min(dp[i][0],c[j]);
	}
	for(int i=n;i>=1;--i) {
		for(int j=n;j>i;--j)if(s[j]>s[i])dp[i][1]=min(dp[i][1],c[j]);
	}
	for(int i=1;i<=n;++i)if(dp[i][0]!=inf&&dp[i][1]!=inf)ans=min(ans,c[i]+dp[i][0]+dp[i][1]);
	if(ans!=1e15)cout<<ans<<endl;
	else cout<<-1<<endl;
	return 0;
}