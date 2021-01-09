#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
const int mod=10000007;
LL n;
int num[51],tot;
int dp[51][51];
int dfs(int pos,int limit,int now) {
	if(!pos)return max(now,1);
	if(!limit&&~dp[pos][now])return dp[pos][now];
	int up=limit?num[pos]:1,res=1;
	for(int i=0;i<=up;++i)
		res=1ll*res*dfs(pos-1,limit&&i==up,now+i)%mod;
	if(!limit)dp[pos][now]=res;
	return res;
}
int solve(LL x) {
	while(x)num[++tot]=x&1ll,x>>=1ll;
	return dfs(tot,1,0);
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	memset(dp,-1,sizeof(dp));
	cin>>n,cout<<solve(n)<<'\n';
	return 0;
}