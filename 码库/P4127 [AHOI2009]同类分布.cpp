#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define int long long
#define rint register int
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
LL a,b,dp[20][20*9][20*9];
int tot,num[20],mod;
LL dfs(int pos,int limit,int sum,int rem) {
    if(sum>mod||sum+9*pos<mod)return 0;
    if(!pos)return sum==mod&&!rem;
    if(!limit&&~dp[pos][sum][rem])return dp[pos][sum][rem];
    int up=limit?num[pos]:9;LL res=0;
    for(int i=0;i<=up;++i)
        res+=dfs(pos-1,limit&&i==up,sum+i,(rem*10+i)%mod);
    if(!limit)dp[pos][sum][rem]=res;
    return res;
}
LL solve(LL x) {
    tot=0;
    LL res=0;
    while(x)num[++tot]=x%10,x/=10;
    for(mod=1;mod<=9*tot;++mod) {
        memset(dp,-1,sizeof(dp));
        res+=dfs(tot,1,0,0);
    }
    return res;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    memset(dp,-1,sizeof(dp));
    cin>>a>>b;
    cout<<(solve(b)-solve(a-1))<<'\n';
    return 0;
}