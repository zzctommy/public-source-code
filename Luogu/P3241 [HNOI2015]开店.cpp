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
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=150010;
struct edge {
	int nxt,to,val;
}e[N<<1];
int n,Q,A,X[N];
LL ans,ST[20][N<<1],dis[N]; 
int lg[N<<1],dfn[N],pw2[30],timer;
int head[N],num_edge;
int mx[N],root,siz[N],totsize,used[N],RT;
int vt[N];
struct node {
	int x;LL p[3];
	node(){}
	node(int a,LL b=0,LL c=0,LL d=0){x=a,p[0]=b,p[1]=c,p[2]=d;}
	bool operator < (const node &rhs)const{return x<rhs.x;}
	node operator + (const node &rhs)const{return node(x,p[0]+rhs.p[0],p[1]+rhs.p[1],p[2]+rhs.p[2]);}
	node operator - (const node &rhs)const{return node(x,p[0]-rhs.p[0],p[1]-rhs.p[1],p[2]-rhs.p[2]);}
};
vector<node>q[N];
void addedge(int fr,int to,int val) {
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	e[num_edge].val=val;
	head[fr]=num_edge;
}
void dfs_ST(int u) {
	dfn[u]=++timer,ST[0][timer]=dis[u];
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;if(dfn[v])continue;
		dis[v]=dis[u]+e[i].val,dfs_ST(v),++timer,ST[0][timer]=dis[u];
	}
}
void init_ST() {
	dfs_ST(1),lg[0]=-1,pw2[0]=1;
	for(int i=1;i<=(n<<1);++i)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=21;++i)pw2[i]=pw2[i-1]<<1;
	for(int i=1;i<=lg[n<<1];++i)
		for(int j=1;j<=(n<<1)-pw2[i]+1;++j)
			ST[i][j]=min(ST[i-1][j],ST[i-1][j+pw2[i-1]]);
}
int Dis(int x,int y) {
	if(dfn[x]>dfn[y])x^=y^=x^=y;int l=dfn[x],r=dfn[y],t=lg[r-l+1];
	return dis[x]+dis[y]-(min(ST[t][l],ST[t][r-pw2[t]+1])<<1);
}
void getrt(int u,int ft) {
	mx[u]=0,siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft||used[v])continue;
		getrt(v,u);
		siz[u]+=siz[v],mx[u]=max(mx[u],siz[v]);
	}
	mx[u]=max(mx[u],totsize-siz[u]);
	if(mx[u]<mx[root])root=u;
}
void dfs(int u,int ft,int rt) {
	q[rt].pb(node(X[u],1,Dis(u,rt),vt[rt]?Dis(u,vt[rt]):0));
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft||used[v])continue;
		dfs(v,u,rt);
	}
}
void divide(int u) {
	used[u]=1,dfs(u,0,u),q[u].pb(node(-1));
	sort(q[u].begin(),q[u].end());
	for(uint i=1;i<q[u].size();++i)q[u][i]=q[u][i]+q[u][i-1];
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(used[v])continue;
		totsize=siz[v],root=0;
		getrt(v,u);
		vt[root]=u;
		divide(root);
	}
}
typedef vector<node>::iterator IT;
node fyyAKIOI(int u,int l,int r) {
	IT itr=upper_bound(q[u].begin(),q[u].end(),node(r));--itr;
	IT itl=upper_bound(q[u].begin(),q[u].end(),node(l-1));--itl;
	return *itr-*itl;
}
LL query(int u,int l,int r) {
	LL res=0;
	for(int p=u;p;p=vt[p]) {
		node t=fyyAKIOI(p,l,r);
		res+=t.p[1];
		if(vt[p])res-=t.p[0]*Dis(u,vt[p])+t.p[2];
		res+=t.p[0]*Dis(u,p);
	}
	return res;
}
signed main() {
	n=rd(),Q=rd(),A=rd();
	for(int i=1;i<=n;++i)X[i]=rd();
	for(int i=1;i<n;++i) {
		int x=rd(),y=rd(),z=rd();
		addedge(x,y,z),addedge(y,x,z);
	} 
	init_ST();
	totsize=mx[root=0]=n,getrt(1,0),divide(RT=root);
	while(Q--) {
		int u=rd(),a=rd(),b=rd(),l=(a+ans)%A,r=(b+ans)%A;
		if(l>r)l^=r^=l^=r;printf("%lld\n",ans=query(u,l,r)); 
	}
	return 0;
}
