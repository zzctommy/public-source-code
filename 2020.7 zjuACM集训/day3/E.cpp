#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define pii pair<int,int>
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=3e5+10;
struct edge {
	int to,nxt;
}e[N<<1];
struct BIT {
	int tr[N],n;
	void init(int t) {
		n=t;
		fill(tr,tr+n+1,0);
	}
	void add(int x,int d) {
		for(rint i=x;i<=n;i+=i&-i)
			tr[i]+=d;
	}
	int ask(int x) {
		int res=0;
		for(rint i=x;i>0;i-=i&-i)
			res+=tr[i];
		return res;
	}
	int ask(int l,int r) {
		return ask(r)-ask(l-1);
	}
}tr;
pii t[N];
int head[N],num_edge;
void addedge(int fr,int to) {
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
} 
int n,siz[N],fa[N],dfn[N],timer;
LL ans;
void dfs(int u,int ft) {
	siz[u]=1,dfn[u]=++timer;
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft)continue;
		fa[v]=u;
		dfs(v,u);
		siz[u]+=siz[v];
	}
}
void calc(int u,int k) {
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==fa[u])ans+=1ll*siz[u]*(tr.ask(1,n)-tr.ask(dfn[u],dfn[u]+siz[u]-1));
		else ans+=1ll*(n-siz[v])*tr.ask(dfn[v],dfn[v]+siz[v]-1);
	}
}
signed main() {
	n=rd(),tr.init(n);
	for(rint i=1;i<=n;++i)t[i].first=rd(),t[i].second=i;
	for(rint i=1;i<n;++i) {
		int x=rd(),y=rd();
		addedge(x,y),addedge(y,x);
	}
	dfs(1,0);
	sort(t+1,t+n+1);
	vector<int>r;
	for(rint i=1;i<=n;++i) {
		r.clear();
		r.pb(t[i].second);
		while(i<n&&t[i].first==t[i+1].first)r.pb(t[++i].second);
		for(uint j=0;j<r.size();++j)calc(r[j],i-1);
		for(uint j=0;j<r.size();++j)tr.add(dfn[r[j]],1);
	}
	printf("%lld\n",ans);
	return 0;
}
