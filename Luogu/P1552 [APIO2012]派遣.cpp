#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=1e5+10;
const int inf=1<<29;
int n,m;
int root;
int L[N];
int num_edge,head[N];
int val[N],fa[N],ls[N],rs[N],dst[N],siz[N];
LL sum[N];
LL ans;
struct edge {
	int nxt,to;
}e[N];
void addedge(int from,int to) {
	++num_edge;
	e[num_edge].nxt=head[from];
	e[num_edge].to=to;
	head[from]=num_edge;
}
int merge(int x,int y) {
	if(!x||!y)return x|y;
	if(val[x]<val[y]||(val[x]==val[y]&&x>y))swap(x,y);
	siz[x]+=siz[y],sum[x]+=sum[y],rs[x]=merge(rs[x],y),fa[rs[x]]=x;
	if(dst[ls[x]]<dst[rs[x]])swap(ls[x],rs[x]);
	dst[x]=dst[rs[x]]+1;
	return x;
}
int find(int x) {return x==fa[x]?x:fa[x]=find(fa[x]);}
void pop(int x) {
	x=find(x),siz[x]=0,sum[x]=0,val[x]=0;
	fa[ls[x]]=ls[x],fa[rs[x]]=rs[x];
	fa[x]=merge(ls[x],rs[x]);
}
void dfs(int u) {
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		dfs(v);
		merge(find(u),find(v));
	}
	while(sum[find(u)]>m)pop(u);
	ans=max(ans,1ll*L[u]*siz[find(u)]);
}
signed main() {
	n=rd(),m=rd();
	for(rint i=1;i<=n;++i) {
		int x=rd();
		sum[i]=val[i]=rd(),L[i]=rd();
		fa[i]=i,siz[i]=1;
		if(x)addedge(x,i);
		else root=i;
	}
	dfs(root);
	printf("%lld\n",ans);
	return 0;
}
