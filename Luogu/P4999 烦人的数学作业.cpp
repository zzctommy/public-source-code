#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)

#define fyyAKNOI return 0;
//Start----------------------------------------------------------------------------
const int lqx=1000000007;
int T;
LL l,r;
int num[20],tot;
int dp[20][200];
int dfs(int pos,int limit,int val) {
	if(!pos)return val;
	if(!limit&&~dp[pos][val])return dp[pos][val];
	int up=limit?num[pos]:9,res=0;
	for(int i=0;i<=up;++i)
		res=(res+dfs(pos-1,limit&&i==up,val+i))%lqx;
	if(!limit)dp[pos][val]=res;
	return res;
}
int solve(LL x) {
	tot=0;
	while(x)num[++tot]=x%10,x/=10;
	return dfs(tot,1,0);
}
void Main() {
	cin>>l>>r;
	cout<<(solve(r)-solve(l-1)+lqx)%lqx<<endl;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	memset(dp,-1,sizeof(dp));
	while(T-->0)Main();
	fyyAKNOI
}