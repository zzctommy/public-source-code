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
int rdc(){
	char ch=getchar();
	while(!isalpha(ch))ch=getchar();
	return ch-'a';
}
#define N 400005
int n,m,ch[N][26],ed[N],to[N],ln[N],rn[N],tmr,tr[N],tot,ans[N],fail[N],trie[N][26],cnt;
vector<int>e[N],q[N];
void insert(char*str,int id){
	int u=0;
	for(int i=0,len=strlen(str);i<len;++i){
		int c=str[i]-'a';
		if(!ch[u][c])ch[u][c]=++cnt;
		u=ch[u][c];
	}
	ed[id]=u;
}
void build_fail(){
	queue<int>q;
	for(int i=0;i<26;++i)if(ch[0][i])q.push(ch[0][i]);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<26;++i)
			if(ch[u][i])fail[ch[u][i]]=ch[fail[u]][i],q.push(ch[u][i]);
			else ch[u][i]=ch[fail[u]][i];
	}
	for(int i=1;i<=cnt;++i)e[fail[i]].pb(i);
}
void dfs1(int u){
	ln[u]=++tmr;
	for(int v:e[u])dfs1(v);
	rn[u]=tmr;
}
void add(int x,int d){if(!x)return;for(int i=x;i<=tmr;i+=i&-i)tr[i]+=d;}
int ask(int x){int res=0;for(int i=x;i>0;i-=i&-i)res+=tr[i];return res;}
void dfs2(int u1,int u2){
	// cerr<<"dfs2:"<<u1<<' '<<u2<<'\n';
	// cerr<<u2<<' '<<ln[u2]<<'\n';
	add(ln[u2],1);
	for(int i:q[u1])ans[i]=ask(rn[ed[i]])-ask(ln[ed[i]]-1);
	for(int i=0;i<26;++i)if(trie[u1][i])dfs2(trie[u1][i],ch[u2][i]);
	add(ln[u2],-1);
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i){
		int op=read(),pre=0,x;
		if(op==2)pre=read();
		x=rdc();
		if(!trie[to[pre]][x])trie[to[pre]][x]=++tot;
		to[i]=trie[to[pre]][x];
	}
	m=read();
	for(int i=1;i<=m;++i){
		int x=read();static char str[N];
		scanf("%s",str);
		insert(str,i),q[to[x]].pb(i);
	}
	// cerr<<"qwq\n";
	build_fail(),dfs1(0),dfs2(0,0);
	for(int i=1;i<=m;++i)printf("%d\n",ans[i]);
	return 0;
}