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
int n,k,ch[305][3],tot,cnt[305],dp[305][1005],fail[305];
vector<int>e[305];
void insert(char*str){
	int u=0,len=strlen(str);
	for(int i=0;i<len;++i){
		int c=str[i]-'A';
		if(!ch[u][c])ch[u][c]=++tot;
		u=ch[u][c];
	}
	++cnt[u];
}
void build_fail(){
	queue<int>q;
	for(int i=0;i<3;++i)if(ch[0][i])q.push(ch[0][i]);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<3;++i)
			if(ch[u][i])fail[ch[u][i]]=ch[fail[u]][i],q.push(ch[u][i]);
			else ch[u][i]=ch[fail[u]][i];
	}
	for(int i=1;i<=tot;++i)e[fail[i]].pb(i);
}
void dfs1(int u){
	for(int v:e[u])cnt[v]+=cnt[u],dfs1(v);
}
int dfs2(int u,int k){
	if(~dp[u][k])return dp[u][k];
	if(!k)return cnt[u];
	int res=0;
	for(int i=0;i<3;++i)res=max(res,dfs2(ch[u][i],k-1));
	return dp[u][k]=res+cnt[u];
}
signed main(){
	n=read(),k=read();
	for(int i=1;i<=n;++i){
		static char str[20];
		scanf("%s",str),insert(str);
	}
	build_fail(),dfs1(0);
	memset(dp,-1,sizeof(dp));
	printf("%d\n",dfs2(0,k));
}