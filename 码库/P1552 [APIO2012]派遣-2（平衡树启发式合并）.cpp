#include<bits/stdc++.h>
using namespace std;
#define rint register int
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
typedef long long LL;
const int N=5e6+10; 
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
struct edge {
	int nxt,to;
}e[N];
int num_edge,head[N];
int n,m,rt[N],L[N],root;
LL ans,sum[N];
int ch[N][2],val[N],siz[N],rnd[N],tot;
void addedge(int from,int to) {
	++num_edge;
	e[num_edge].nxt=head[from];
	e[num_edge].to=to;
	head[from]=num_edge;
}
int New(int v) {
	int t=++tot;
	val[t]=sum[t]=v;
	rnd[t]=rand();
	siz[t]=1;
	return t;
}
void pushup(int x) {
	siz[x]=siz[ch[x][0]]+1+siz[ch[x][1]];
	sum[x]=sum[ch[x][0]]+val[x]+sum[ch[x][1]];
}
int merge(int x,int y) {
	if(!x||!y)return x|y;
	if(rnd[x]<rnd[y]) {
		ch[x][1]=merge(ch[x][1],y);
		pushup(x);return x;
	} else {
		ch[y][0]=merge(x,ch[y][0]);
		pushup(y);return y;
	}
}
void split(int u,int k,int &x,int &y) {
	if(!u) {x=y=0;return;}
	if(val[u]<=k)x=u,split(ch[u][1],k,ch[u][1],y);
	else y=u,split(ch[u][0],k,x,ch[u][0]);
	pushup(u);
}
void del(int &u,int x) {
	int a,b,c;
	split(u,x,a,b);
	split(a,x-1,a,c);
	c=merge(ch[c][0],ch[c][1]);
	u=merge(merge(a,c),b);
}
int kth(int u,int k) {
	while(true) {
		if(k<=siz[ch[u][0]])u=ch[u][0];	
		else {
			if(k==siz[ch[u][0]]+1)return val[u];
			else k-=siz[ch[u][0]]+1,u=ch[u][1];
		}
	}
}
void insert(int &x,int v) {
	int a,b;
	split(x,v,a,b);
	x=merge(merge(a,New(v)),b);
}
void dfs(int x,int &y) {
	if(!x)return;
	if(ch[x][0])dfs(ch[x][0],y);
	insert(y,val[x]);
	if(ch[x][1])dfs(ch[x][1],y);
}
int dsu(int x,int y) {
	if(siz[x]>siz[y])x^=y^=x^=y;
	dfs(x,y);return y;
}
void dfs(int u) {
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		dfs(v);
		rt[u]=dsu(rt[u],rt[v]);
	}
	while(sum[rt[u]]>m)del(rt[u],kth(rt[u],siz[rt[u]]));
	ans=max(ans,1ll*L[u]*siz[rt[u]]);
}
signed main() {
	n=rd(),m=rd();
	for(rint i=1;i<=n;++i) {
		int x=rd(),y=rd();
		L[i]=rd();
		if(x)addedge(x,i);
		else root=i;
		rt[i]=New(y);
	}
	dfs(root);
	printf("%lld\n",ans);
	return 0;
}
