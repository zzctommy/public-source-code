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
string T,str[N];
int n,f[N],g[N];
LL cnt[N];
int ch[N][26],tot,fail[N];
LL ans;
vector<int>e[N];
void clear(){
	for(int i=0;i<=tot;++i)e[i].clear();
	tot=0;
	memset(cnt,0,sizeof(cnt));
	memset(ch,0,sizeof(ch));
	memset(fail,0,sizeof(fail));
}
void insert(string str){
	int u=0;
	for(int i=0;i<sz(str);++i){
		int c=str[i]-'a';
		if(!ch[u][c])ch[u][c]=++tot;
		u=ch[u][c];
	}
	++cnt[u];
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
	for(int v:e[u])cnt[v]+=cnt[u],dfs(v);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T>>n;
	for(int i=1;i<=n;++i)cin>>str[i];

	for(int i=1;i<=n;++i)insert(str[i]);
	build_fail(),dfs(0);
	for(int u=0,i=0;i<sz(T);++i)u=ch[u][T[i]-'a'],f[i]=cnt[u];
	// cout<<"cnt:";for(int i=0;i<=tot;++i)cout<<cnt[i]<<' ';cout<<'\n';
	// cout<<"fail:";for(int i=0;i<=tot;++i)cout<<fail[i]<<' ';cout<<'\n';

	clear();
	for(int i=1;i<=n;++i)reverse(str[i].begin(),str[i].end()),insert(str[i]);
	build_fail(),dfs(0);
	// for(int u=0,i=sz(T)-1;~i;--i)u=ch[u][T[i]-'a'],g[i]=cnt[u];
	for(int u=0,i=sz(T)-1;~i;--i)u=ch[u][T[i]-'a'],g[i]=cnt[u];
	// cout<<"f:";for(int i=0;i<sz(T);++i)cout<<f[i]<<' ';cout<<'\n';
	// cout<<"g:";for(int i=0;i<sz(T);++i)cout<<g[i]<<' ';cout<<'\n';

	for(int i=1;i<sz(T);++i)ans+=1ll*f[i-1]*g[i];
	cout<<ans<<'\n';
	return 0;
}
/*
abcdabcd
4
d
cd
a
ab

*/