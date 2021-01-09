#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return x*f;
}
#define pb push_back
const int N=2e5+10;
int n,k;
LL ans;
struct node {
	int siz,dep;
}a[N];
vector<int>g[N];
void dfs(int u,int ft) {
	a[u].siz=1;
	for(rint i=0;i<g[u].size();++i) {
		int v=g[u][i];
		if(v==ft)continue;
		a[v].dep=a[u].dep+1;
		dfs(v,u);
		a[u].siz+=a[v].siz;
	}
}
bool cmp(const node &a,const node &b) {
	return a.dep-a.siz>b.dep-b.siz;
}
signed main() {
	n=rd(),k=rd();
	for(rint i=1;i<n;++i) {
		int x=rd(),y=rd();
		g[x].pb(y),g[y].pb(x);
	}
	dfs(1,0);
	sort(a+1,a+n+1,cmp);
	for(rint i=1;i<=k;++i)
		ans+=a[i].dep-a[i].siz+1;
	printf("%lld\n",ans);
	return 0;
}