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
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)) {
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=200009;
vector<int>v[N],g[N];
queue<int>q;
int n,m,F[N],col[N],cnt;
int find(int x) {
	return x==F[x]?x:F[x]=find(F[x]);
}
int merge(int x,int y) {
	x=find(x),y=find(y);
	if(v[x].size()>v[y].size())x^=y^=x^=y;
	for(int i:v[x])v[y].pb(i),F[i]=y;
	for(int i:g[x])g[y].pb(i);
	return y;
}
void bfs() {
	while(!q.empty()) {
		int u=q.front(),rt;q.pop();
		if(g[u].size()<2)continue;
		vector<int>fyyAKIOI,t=g[u];
		g[u].swap(fyyAKIOI);
		rt=find(t[0]);
		for(uint i=1;i<t.size();++i)
			if(find(rt)!=find(t[i]))rt=merge(rt,t[i]);
		g[u].pb(rt),q.push(rt);
	}
}
signed main() {
	n=rd(),m=rd();
	for(int i=1; i<=m; ++i) {
		int x=rd(),y=rd();
		g[x].pb(y);
	}
	for(int i=1; i<=n; ++i)F[i]=i,v[i].pb(i),q.push(i);
	bfs();
	for(int i=1; i<=n; ++i) {
		if(col[i])continue;
		int fx=find(i);++cnt;
		for(int j:v[fx])col[j]=cnt;
	}
	for(int i=1; i<=n; ++i)printf("%d\n",col[i]);
	return 0;
}
