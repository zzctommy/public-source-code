#include<bits/stdc++.h>
using namespace std;
#define rint register int
typedef long long LL;
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
inline int min(const int &a,const int &b) {return a<b?a:b;}
inline int max(const int &a,const int &b) {return a>b?a:b;}
const int N=100010;
const int M=4000010;
const int mod=1000000000;
const double alpha=0.8;
const double beta=0.7;
int n,val[N];
LL ans;
int head[N],num_edge;
int fa[18][N],bin[18],dep[N],dist[N];
int mx[N],siz[N],root,vt[N],totsize;
bool used[N];
int rub[M],rub_top,st[M],st_top,num_node;
int sz[M],ch[M][2],key[M];
int t1[N],t2[N];
vector<int>to[N];
struct egde {
	int to,nxt;
}e[N<<1];
void addedge(int from,int to) {
	++num_edge;
	e[num_edge].nxt=head[from];
	e[num_edge].to=to;
	head[from]=num_edge;
}
int lca(int x,int y) {
	if(dep[x]<dep[y])x^=y^=x^=y;
	int delta=dep[x]-dep[y];
	for(rint i=17;i>=0;--i)if(delta&bin[i])x=fa[i][x];
	if(x==y)return x;
	for(rint i=17;i>=0;--i)if(fa[i][x]!=fa[i][y])x=fa[i][x],y=fa[i][y];
	return fa[0][x];
}
LL dis(int x,int y) {return dist[x]+dist[y]-(dist[lca(x,y)]<<1);}
void push_in_rub(int u) {
	if(!u)return;
	push_in_rub(ch[u][0]);
	rub[++rub_top]=u;
	push_in_rub(ch[u][1]);
	ch[u][0]=ch[u][1]=sz[u]=key[u]=0;
}
void pushup(int u) {
	sz[u]=sz[ch[u][0]]+sz[ch[u][1]]+1;
}
void push_in_st(int u) {
	if(!u)return;
	push_in_st(ch[u][0]);
	st[++st_top]=u;
	push_in_st(ch[u][1]);
	ch[u][0]=ch[u][1]=0;
}
int getnew() {
	return rub_top?rub[rub_top--]:++num_node;
}
void build(int &x,int l,int r) {
	if(l>r)return;
	int mid=(l+r)>>1;
	x=st[mid];sz[x]=r-l+1;
	build(ch[x][0],l,mid-1);
	build(ch[x][1],mid+1,r);
}
void rebuild(int &u) {
	st_top=0;push_in_st(u);
	build(u,1,st_top);
}
void insert(int &u,int val) {
	if(!u) {u=getnew(),key[u]=val,sz[u]=1;return;}
	if(val<=key[u])insert(ch[u][0],val);
	else insert(ch[u][1],val);
	pushup(u);
	if(sz[ch[u][0]]>1.0*sz[u]*beta)rebuild(u);
	if(sz[ch[u][1]]>1.0*sz[u]*beta)rebuild(u);
}
int rk(int u,int val) {
	int res=0,now=u;
	while(now) {
		if(key[now]<val)res+=sz[ch[now][0]]+1,now=ch[now][1];
		else now=ch[now][0];
	}
	return res;
}
void getroot(int u,int ft) {
	mx[u]=0,siz[u]=1;
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft||used[v])continue;
		getroot(v,u);
		siz[u]+=siz[v];
		mx[u]=max(mx[u],siz[v]);
	}
	mx[u]=max(mx[u],totsize-siz[u]);
	if(mx[root]>mx[u])root=u;
}
void calc(int u,int ft,int Vt) {
	insert(t1[Vt],dis(u,Vt)-val[u]);
	if(vt[Vt])insert(t2[Vt],dis(u,vt[Vt])-val[u]);
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft||used[v])continue;
		calc(v,u,Vt);
	}
}
void dfs_build(int u) {
	calc(u,0,u);used[u]=1;
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(used[v])continue;
		totsize=siz[v];
		root=0;
		getroot(v,0);
		vt[root]=u;
		to[u].push_back(root);
		dfs_build(root);
	}
}
void dfs_pia(int u) {
	++totsize;used[u]=0;
	push_in_rub(t1[u]);
	push_in_rub(t2[u]);
	t1[u]=t2[u]=0;
	for(rint i=0;i<to[u].size();++i)
		dfs_pia(to[u][i]);
	to[u].clear();
}
void dfs_rebuild(int u) {
	totsize=0;dfs_pia(u);root=0;getroot(u,0);
	if(vt[u])
		for(rint i=0;i<to[vt[u]].size();++i)
			if(to[vt[u]][i]==u)to[vt[u]][i]=root;
	vt[root]=vt[u];dfs_build(root);
}
void dfs_insert(int x) {
	for(rint i=x;vt[i];i=vt[i]) {
		int tmp=val[x]-dis(x,vt[i])+1;
		ans+=rk(t1[vt[i]],tmp)-rk(t2[i],tmp);
	}
	for(rint i=x;i;i=vt[i]) {
		insert(t1[i],dis(i,x)-val[x]);
		if(vt[i])insert(t2[i],dis(x,vt[i])-val[x]);
	}
	int res=0;
	for(rint i=x;vt[i];i=vt[i])
		if(sz[t1[i]]>1.0*sz[t1[vt[i]]]*alpha)res=vt[i];
	if(res)dfs_rebuild(res);
}
signed main() {
	rd(),n=rd();
	bin[0]=1;for(rint i=1;i<=17;++i)bin[i]=bin[i-1]<<1;
	mx[root=0]=n;
	for(rint i=1;i<=n;++i) {
		vt[i]=fa[0][i]=(rd()^(ans%mod));
		int c=rd();val[i]=rd();used[i]=1;
		dep[i]=dep[fa[0][i]]+1;
		dist[i]=dist[fa[0][i]]+c;
		for(rint j=1;j<=17;++j)fa[j][i]=fa[j-1][fa[j-1][i]];
		if(vt[i])to[vt[i]].push_back(i),addedge(i,fa[0][i]),addedge(fa[0][i],i);
		dfs_insert(i);printf("%lld\n",ans);
	}
	return 0;
} 
