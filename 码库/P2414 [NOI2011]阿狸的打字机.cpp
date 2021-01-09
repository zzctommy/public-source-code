#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100010;
int num,tot,Q;
int ans[N];
int tr[N];
int ln[N],rn[N],timer;
int ch[N][26],fa[N],fail[N],ed[N];
char s[N];
vector<int>g[N];
struct node {
	int id,x;
	node(){}
	node(int a,int b){id=a,x=b;}
};
vector<node>q[N];
void Build_Trie(char*s) {
	int u=0,len=strlen(s);
	for(int i=0;i<len;++i) {
		if(s[i]=='B') u=fa[u];
		else if(s[i]=='P')ed[++num]=u;
		else {
			int c=s[i]-'a';
			if(!ch[u][c])ch[u][c]=++tot;
			fa[ch[u][c]]=u,u=ch[u][c];
		}
	}
}
void build_fail() {
	queue<int>q;
	for(int i=0;i<26;++i)if(ch[0][i])q.push(ch[0][i]);
	while(!q.empty()) {
		int u=q.front();q.pop();
		for(int i=0;i<26;++i)
			if(ch[u][i])fail[ch[u][i]]=ch[fail[u]][i],q.push(ch[u][i]);
			else ch[u][i]=ch[fail[u]][i];
	}
	for(int i=1;i<=tot;++i)g[fail[i]].pb(i);
}
void dfs(int u) {
	ln[u]=++timer;
	for(int v:g[u])dfs(v);
	rn[u]=timer;
}
void add(int x,int d){
	for(int i=x;i<=timer;i+=i&-i)tr[i]+=d;
}
int ask(int x){
	int res=0;
	for(int i=x;i>0;i-=i&-i)res+=tr[i];
	return res;
}
void solve() {
	int len=strlen(s),u=0,nq=0;
	for(int i=0;i<len;++i) {
		if(s[i]=='P') {
			++nq;
			for(uint j=0;j<q[nq].size();++j) {
				int id=q[nq][j].id,x=q[nq][j].x;
				ans[id]=ask(rn[ed[x]])-ask(ln[ed[x]]-1);
			}
		} else if(s[i]=='B')add(ln[u],-1),u=fa[u];
		else u=ch[u][s[i]-'a'],add(ln[u],1);
	}
}
signed main() {
	scanf("%s",s);
	Build_Trie(s),build_fail(),dfs(0);
	Q=rd();
	for(int i=1;i<=Q;++i) {
		int x=rd(),y=rd();
		q[y].pb(node(i,x));
	}
	solve();
	for(int i=1;i<=Q;++i)printf("%d\n",ans[i]);
	return 0;
}