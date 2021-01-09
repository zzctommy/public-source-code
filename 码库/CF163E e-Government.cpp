#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb(x) push_back(x)
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
int rdc() {
	char ch=getchar();
	while(ch!='+'&&ch!='-'&&ch!='?')ch=getchar();
	if(ch=='+')return 1;
	else if(ch=='-')return 2;
	return 3;
}
const int N=100010;
const int M=1000010;
int n,k;
bool vis[N];
string S;
int ch[M][26],tot,ed[N],fail[M];
int lp[M],rp[M],timer;
vector<int>g[M];
int tr[M];
void insert(string s,int id) {
	int len=s.length(),u=0;
	for(int i=0;i<len;++i) {
		int c=s[i]-'a';
		if(!ch[u][c])ch[u][c]=++tot;
		u=ch[u][c];
	}
	ed[id]=u;
}
void make_fail() {
	queue<int>q;
	for(int i=0;i<26;++i)
		if(ch[0][i])q.push(ch[0][i]);
	while(!q.empty()) {
		int u=q.front();q.pop();
		for(int i=0;i<26;++i)
			if(ch[u][i])fail[ch[u][i]]=ch[fail[u]][i],q.push(ch[u][i]);
			else ch[u][i]=ch[fail[u]][i];
	}
	for(int i=1;i<=tot;++i)g[fail[i]].pb(i);
}
void dfs(int u) {
	lp[u]=++timer;
	for(int v:g[u])dfs(v);
	rp[u]=timer;
}
void add(int x,int d) {
	for(int i=x;i<=tot+1;i+=i&-i)tr[i]+=d;
}
void add(int l,int r,int d) {
	add(l,d),add(r+1,-d);
}
int ask(int x) {
	int res=0;
	for(int i=x;i>0;i-=i&-i)res+=tr[i];
	return res;
}
signed main() {
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=k;++i)
		cin>>S,insert(S,i);
	make_fail(),dfs(0);
	for(int i=1;i<=k;++i)
		add(lp[ed[i]],rp[ed[i]],1),vis[i]=1;
	for(;n;--n) {
		int opt=rdc();
		if(opt==1) {
			int x=rd();
			if(vis[x])continue;
			vis[x]=1,add(lp[ed[x]],rp[ed[x]],1);
		} else if(opt==2) {
			int x=rd();
			if(!vis[x])continue;
			vis[x]=0,add(lp[ed[x]],rp[ed[x]],-1);
		} else {
			cin>>S;LL res=0;
			for(int i=0,len=S.length(),u=0;i<len;++i)
				u=ch[u][S[i]-'a'],res+=ask(lp[u]);
			cout<<res<<'\n';
		}
	}
	return 0;
}