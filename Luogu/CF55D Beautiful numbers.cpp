#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
int T;
LL l,r;
LL dp[20][2520][48];
int num[20],tot;
int lsh[48]={
1,2,3,4,5,6,7,8,
9,10,12,14,15,18,20,21,
24,28,30,35,36,40,42,45,
56,60,63,70,72,84,90,105,
120,126,140,168,180,210,252,280,
315,360,420,504,630,840,1260,2520
},rev[2521];
int gcd(int x,int y) {return !y?x:gcd(y,x%y);}
LL dfs(int pos,int limit,int rem,int lcm) {
    if(!pos)return !(rem%lcm);
    if(!limit&&~dp[pos][rem][rev[lcm]])return dp[pos][rem][rev[lcm]];
    int up=limit?num[pos]:9;LL res=0;
    for(int i=0;i<=up;++i)
        res+=dfs(pos-1,limit&(i==up),(rem*10+i)%2520,i?lcm*i/gcd(lcm,i):lcm);
    if(!limit)dp[pos][rem][rev[lcm]]=res;
    return res;
}
LL solve(LL x) {
    tot=0;
    while(x)num[++tot]=x%10,x/=10;
    return dfs(tot,1,0,1);
}
void init() {for(int i=0;i<48;++i)rev[lsh[i]]=i;}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    init(),cin>>T;
    memset(dp,-1,sizeof(dp));
    while(T--)cin>>l>>r,cout<<solve(r)-solve(l-1)<<'\n';
    return 0;
}