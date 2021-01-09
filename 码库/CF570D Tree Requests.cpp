#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
#define pb push_back
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int rdc() {
	char c=getchar();
	while(!isalpha(c))c=getchar();
	return c-'a';
}
const int N=500010;
int n,m,a[N],ans[N];
int siz[N],son[N],dep[N],cnt[N];
vector<pair<int,int> >que[N];
vector<int>g[N];
void dfs1(int u) {
	siz[u]=1;
	for(rint i=0;i<g[u].size();++i) {
		int v=g[u][i];
		dep[v]=dep[u]+1;
		dfs1(v);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void calc(int u,int sn) {
	cnt[dep[u]]^=1<<a[u];
	for(rint i=0;i<g[u].size();++i) {
		int v=g[u][i];
		if(v==sn)continue;
		calc(v,sn);
	}
}
int check(int x) {
	x-=x&-x;
	return !x;
}
void clear(int u) {
	cnt[dep[u]]^=1<<a[u];
	for(rint i=0;i<g[u].size();++i)clear(g[u][i]);
}
void dfs(int u,int keep) {
	for(rint i=0;i<g[u].size();++i) {
		int v=g[u][i];
		if(v==son[u])continue;
		dfs(v,0);
	}
	if(son[u])dfs(son[u],1);
	calc(u,son[u]);
	for(vector<pair<int,int> >::iterator it=que[u].begin();it!=que[u].end();++it)
		ans[it->second]=check(cnt[it->first]);
	if(!keep) {
		cnt[dep[u]]^=1<<a[u];
		for(rint i=0;i<g[u].size();++i)clear(g[u][i]);
	}
}
signed main() {
	n=rd(),m=rd();
	for(rint i=2;i<=n;++i)g[rd()].pb(i);
	for(rint i=1;i<=n;++i)a[i]=rdc();
	for(rint i=1;i<=m;++i) {
		int x=rd(),y=rd();
		que[x].pb(make_pair(y,i));
	}
	dep[1]=1,dfs1(1),dfs(1,1);
	for(rint i=1;i<=m;++i)puts(ans[i]?"Yes":"No");
	return 0;
}