#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
#define int long long
const int N=1009;
const int mod=1000000007;
char s[N],t[N];
int num[N],tot;
int ans,dp[N][10][10];
int dfs(int pos,int limit,int lead,int pre1,int pre2) {
    if(!pos)return 1;
    if(!limit&&!lead&&~pre1&&~pre2&&~dp[pos][pre1][pre2])return dp[pos][pre1][pre2];
    int up=limit?num[pos]:9,res=0;
    for(int i=0;i<=up;++i)
        if(lead)res=(res+dfs(pos-1,limit&&i==up,lead&&!i,!i?-1:i,-1))%mod;
        else if(i!=pre1&&i!=pre2&&!lead)res=(res+dfs(pos-1,limit&&i==up,0,i,pre1))%mod;
    if(!limit&&!lead&&~pre1&&~pre2)dp[pos][pre1][pre2]=res;
    return res;
}
int solve(char*s) {
    tot=0;
    int res=0;
    for(int len=strlen(s+1),i=len;i>0;--i)num[++tot]=s[i]-'0';
    return dfs(tot,1,1,-1,-1);
}
int ok(char*s) {
    int len=strlen(s+1);
    for(int i=2;i<=len;++i)if(s[i]==s[i-1]||s[i]==s[i-2])return 1;
    return 0;
}
int to_num(char*s) {
    int res=0,len=strlen(s+1);
    for(int i=1;i<=len;++i)res=1ll*(res*10+s[i]-'0')%mod;
    return res;
}
signed main() {
    memset(dp,-1,sizeof(dp));
    scanf("%s%s",s+1,t+1);
    printf("%lld\n",(to_num(t)-to_num(s)+1+mod-(solve(t)-(solve(s)+ok(s)-1)+mod)%mod+mod)%mod);
    return 0;
}