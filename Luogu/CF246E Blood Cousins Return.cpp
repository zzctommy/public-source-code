#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
#define N 300009
int n,q,hash_tot,id[N],ans[N];
int son[N],dep[N],siz[N];
int cnt[N<<1];
bool vis[N];
vector<pair<int,int> >v[N];
vector<int>g[N];
map<string,int>name;
map<int,bool>mp[N];
void dfs1(int u) {
	siz[u]=1;
	for(int v:g[u]) {
		dep[v]=dep[u]+1,dfs1(v),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void calc(int u,int sn) {
	if(!mp[dep[u]][id[u]])++cnt[dep[u]],mp[dep[u]][id[u]]=1;
	for(int v:g[u]) if(v!=sn)calc(v,sn);
}
void clear(int u) {
	mp[dep[u]][id[u]]=0,cnt[dep[u]]=0;
	for(int v:g[u])clear(v);
}
void dfs(int u,int cl) {
	vis[u]=1;
	for(int v:g[u])
		if(v!=son[u])dfs(v,1);
	if(son[u])dfs(son[u],0);
	calc(u,son[u]);
	for(pair<int,int> i:v[u])ans[i.first]=cnt[i.second+dep[u]];
	if(cl)clear(u);
}
signed main() {
	// ios::sync_with_stdio(0);
	// cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i) {
		string s;int f;
		cin>>s>>f;
		if(!name[s])name[s]=++hash_tot;
		id[i]=name[s],g[f].pb(i);
	}
	cin>>q;
	for(int i=1;i<=q;++i) {
		int x=rd(),y=rd();
		v[x].pb(mkp(i,y));
	}
	for(int i=1;i<=n;++i)if(!vis[i])dfs1(i),dfs(i,1);
	for(int i=1;i<=q;++i)cout<<ans[i]<<endl;
	return 0;
}