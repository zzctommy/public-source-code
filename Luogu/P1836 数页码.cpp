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
int n;
int num[10],tot;
LL dp[10][100];
LL dfs(int pos,int limit,int val) {
	if(!pos)return val;
	if(!limit&&~dp[pos][val])return dp[pos][val];
	int up=limit?num[pos]:9;LL res=0;
	for(int i=0;i<=up;++i)
		res=res+dfs(pos-1,limit&&i==up,val+i);
	if(!limit)dp[pos][val]=res;
	return res;
}
LL solve(int x) {
	tot=0;
	while(x)num[++tot]=x%10,x/=10;
	return dfs(tot,1,0);
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	memset(dp,-1,sizeof(dp));
	cin>>n,cout<<solve(n)<<endl;
	fyyAKNOI
}