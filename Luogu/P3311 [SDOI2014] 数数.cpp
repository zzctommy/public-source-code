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
#define mod 1000000007
#define N 1505
char n[N];
int m,Len,ch[N][10],tot,dp[N][N][2][2],fail[N];
bool en[N];
void fmod(int&x){x-=mod,x+=x>>31&mod;}
void insert(char*str){
	int u=0,len=strlen(str);
	for(int i=0;i<len;++i){
		int c=str[i]-'0';
		if(!ch[u][c])ch[u][c]=++tot;
		u=ch[u][c];
	}
	en[u]=1;
}
void build_fail(){
	queue<int>q;
	for(int i=0;i<10;++i)if(ch[0][i])q.push(ch[0][i]);
	while(!q.empty()){
		int u=q.front();q.pop();
		en[u]|=en[fail[u]];
		for(int i=0;i<10;++i)
			if(ch[u][i])fail[ch[u][i]]=ch[fail[u]][i],q.push(ch[u][i]);
			else ch[u][i]=ch[fail[u]][i];
	}
}
int dfs(int u,int pos,int limit,int lead){
	if(!pos)return !en[u];
	if(en[u])return 0;
	if(~dp[u][pos][limit][lead])return dp[u][pos][limit][lead];
	int up=limit?n[pos-1]-'0':9,res=0;
	for(int i=0;i<=up;++i)fmod(res+=dfs(lead&&!i?0:ch[u][i],pos-1,limit&&i==up,lead&&!i));
	return dp[u][pos][limit][lead]=res;
}
signed main(){
	scanf("%s%d",n,&m),Len=strlen(n);
	for(int i=1;i<=m;++i){
		static char str[N];
		scanf("%s",str),insert(str);
	}
	build_fail();
	reverse(n,n+Len);
	memset(dp,-1,sizeof(dp));
	printf("%d\n",(dfs(0,Len,1,1)+mod-1)%mod);
	return 0;
}