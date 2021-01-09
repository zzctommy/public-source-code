#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define x first
#define y second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 705
#define mod 1000000007
char s[N];
int d[N],dp[N][N][10];
void fmod(int&x){x-=mod,x+=x>>31&mod;}
int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
int dfs(int pos,int limit,int sum,int low){
	if(!pos)return !sum;
	if(!limit&&~dp[pos][sum][low])return dp[pos][sum][low];
	int res=0,up=limit?d[pos]:9;
	for(int i=0;i<=up;++i)fmod(res+=dfs(pos-1,limit&&i==up,sum-(i>=low),low));
	if(!limit)dp[pos][sum][low]=res;
	return res;
}
int solve(char*s){
	int res=0;
	d[0]=0;int n=strlen(s+1);
	for(int i=1,j=n;i<=n;++i,--j)d[j]=s[i]-'0';
	for(int i=1;i<=9;++i)
		for(int j=1,now=1;j<=n;++j,now=(10ll*now+1)%mod)
			fmod(res+=1ll*dfs(n,1,j,i)*now%mod);
	return res;
}
signed main(){
	memset(dp,-1,sizeof(dp));
	scanf("%s",s+1);
	printf("%d\n",solve(s));
}