#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int M=2000005;
int fail[M],dp[M];
int n,tot,ch[M][26],ed[M];
vector<int>f[M],g[M];
unordered_map<int,bool>mp[M];
void ins(char*s,int id) {
	int u=0,len=strlen(s);
	for(int i=0;i<len;++i) {
		int c=s[i]-'a';
		if(!ch[u][c])ch[u][c]=++tot;
		u=ch[u][c];
	}
	ed[id]=u;
}
void make_fail() {
	queue<int>q;
	for(int i=0;i<26;++i)if(ch[0][i])q.push(ch[0][i]),fail[ch[0][i]]=0;
	while(!q.empty()) {
		int u=q.front();q.pop();
		for(int i=0;i<26;++i)
			if(ch[u][i])q.push(ch[u][i]),fail[ch[u][i]]=ch[fail[u]][i];
			else ch[u][i]=ch[fail[u]][i];
	}
}
void dfs(int u) {
	for(uint i=0;i<g[u].size();++i) {
		int v=g[u][i];dfs(v);
		dp[u]+=dp[v];
	}
}
signed main() {
	n=rd();
	char jpjAKIOI[M];
	for(int i=1;i<=n;++i) {
		scanf("%s",jpjAKIOI);
		ins(jpjAKIOI,i);
	}
	make_fail();
	scanf("%s",jpjAKIOI);
	for(int i=0,u=0,len=strlen(jpjAKIOI);i<len;++i)
		u=ch[u][jpjAKIOI[i]-'a'],++dp[u];
	for(int i=1;i<=tot;++i)g[fail[i]].pb(i);
	dfs(0);
	for(int i=1;i<=n;++i)printf("%d\n",dp[ed[i]]);
	return 0;
}