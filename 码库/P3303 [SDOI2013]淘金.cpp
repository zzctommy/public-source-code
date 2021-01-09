#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//Start---------------------------

//Wanrning!!! I define int long long----------------------------------
#define int long long
//Wanrning!!! I define int long long----------------------------------

const int N=8287;
int n,k,ans;
int num[15],tot;
LL dp[15][N],a[N],cnt;
map<LL,int>mp;
const int zky=1000000007;
int v[N];
struct node {
	int x,y;
	node(){x=y=0;}
	node(int x_,int y_){x=x_,y=y_;}
	inline bool operator <(const node &rhs)const{return 1.*a[x]/a[rhs.y]<1.*a[rhs.x]/a[y];}
};
priority_queue<node>q;
namespace pre_work {
	set<int>s1,s2;set<LL>S;
	int f(int x) {
		int res=1;
		while(x)res*=x%10,x/=10;
		return res;
	}
	void main() {
		for(int i=1;i<=1e6;++i)s1.insert(f(i));
		s2=s1;
		for(int i:s1)
			for(int j:s2)
				S.insert(1ll*i*j);
		for(LL i:S)v[++cnt]=i,mp[i]=cnt;
	}
}
LL dfs(int pos,int limit,LL now) {
	if(!pos)return now==1;
	if(!limit&&~dp[pos][mp[now]])return dp[pos][mp[now]];
	int up=limit?num[pos]:9;LL res=0;
	for(int i=1;i<=up;++i)
		if(now%i==0)res+=dfs(pos-1,limit&&i==up,now/i);
	if(!limit)dp[pos][mp[now]]=res;
	return res;
}
void solve(LL x) {
	memset(dp,-1,sizeof(dp));
	while(x)num[++tot]=x%10,x/=10;
	for(int i=1;i<=cnt;++i)
		for(int j=1;j<=tot;++j)a[i]+=dfs(j,j==tot,v[i]);
}
inline bool cmp(const LL &a,const LL &b) {return a>b;}
signed main() {
	pre_work::main();
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	solve(n);
	sort(a+1,a+cnt+1,cmp);
	for(int i=1;i<=cnt;++i)q.push(node(i,1));
	while(k--) {
		node u=q.top();q.pop();
		ans=(ans+((a[u.x]%zky)*(a[u.y]%zky))%zky)%zky;
		if(u.y+1<=cnt)q.push(node(u.x,u.y+1));
	}
	cout<<ans<<endl;
    return 0;
}