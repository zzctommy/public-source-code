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
#define N 200005
#define Q 500005
int n,q,ans[Q],tot,ch[N][26],fail[N];
int dfn[N],ed[N],tmr,to[N],tr[N];
string str[N];
struct node{
	int op,pos,id;
	node(){op=pos=id=0;}
	node(int o_,int p_,int i_){op=o_,pos=p_,id=i_;}
};
vector<node>v[N];
vector<int>e[N];
void insert(string str,int id){
	int u=0;
	for(int i=0;i<sz(str);++i){
		int c=str[i]-'a';
		if(!ch[u][c])ch[u][c]=++tot;
		u=ch[u][c];
	}
	to[id]=u;
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
	for(int i=1;i<=tot;++i)e[fail[i]].pb(i);
}
void dfs(int u){
	dfn[u]=++tmr;
	for(int v:e[u])dfs(v);
	ed[u]=tmr;
}
void add(int x,int d){for(int i=x;i<=tmr;i+=i&-i)tr[i]+=d;}
int ask(int x){int res=0;for(int i=x;i>0;i-=i&-i)res+=tr[i];return res;}
int ask(int l,int r){return ask(r)-ask(l-1);}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;++i)
		cin>>str[i],insert(str[i],i);
	build_fail(),dfs(0);
	for(int i=1;i<=q;++i){
		int l,r,k;cin>>l>>r>>k;
		v[l-1].pb(node(-1,k,i)),v[r].pb(node(1,k,i));
	}
	for(int i=1;i<=n;++i){
		for(int u=0,j=0;j<sz(str[i]);++j)
			u=ch[u][str[i][j]-'a'],add(dfn[u],1);
		for(node j:v[i])
			ans[j.id]+=j.op*ask(dfn[to[j.pos]],ed[to[j.pos]]);
	}
	for(int i=1;i<=q;++i)cout<<ans[i]<<'\n';
}