//#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
//#define int long long
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return x*f;
}
const int N=3010;
const int mod=998244353;
int dp[N][N];
char s[N],t[N];
int n,m,ans;
signed main() {
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1),m=strlen(t+1);
	for(rint i=1;i<=n;++i)dp[i][i]=(i>m||s[1]==t[i])?2:0;
	for(rint len=2;len<=n;++len) {
		for(rint l=1;l<=n;++l) {
			int r=l+len-1;
			if(r>n)break;
			if(l>m||s[len]==t[l])dp[l][r]=(dp[l][r]+dp[l+1][r])%mod;
			if(r>m||s[len]==t[r])dp[l][r]=(dp[l][r]+dp[l][r-1])%mod;
		}
	}
	for(rint i=m;i<=n;++i)ans=(ans+dp[1][i])%mod;
	printf("%d\n",ans);
	return 0;
}