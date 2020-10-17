#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int rdc(){
	char ch=getchar();
	while(ch!='Q'&&ch!='C')ch=getchar();
	return ch=='Q';
}
const int N=200005;
const LL inf=1e14;
const int T=N<<2;
int n,dp[N];
LL a[N];
int head[N],num_edge;
int dfn[N],rev[N],tmr,fa[N],siz[N],son[N],top[N],ed[N];
struct edge{
	int nxt,to;
}e[N<<1];
void addedge(int fr,int to){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
struct Matrix {
	LL a[2][2];
	Matrix(){a[0][0]=a[0][1]=a[1][0]=a[1][1]=inf;}
	LL*operator[](const int&k){return a[k];}
	Matrix operator * (const Matrix&b){
		Matrix res;
		res[0][0]=min(a[0][0]+b.a[0][0],a[0][1]+b.a[1][0]);
		res[0][1]=min(a[0][0]+b.a[0][1],a[0][1]+b.a[1][1]);
		res[1][0]=min(a[1][0]+b.a[0][0],a[1][1]+b.a[1][0]);
		res[1][1]=min(a[1][0]+b.a[0][1],a[1][1]+b.a[1][1]);
		return res;
	}
	void print(){
		printf("%lld %lld\n%lld %lld\n\n",a[0][0],a[0][1],a[1][0],a[1][1]);
	}
}mat[N],val[T];
void dfs1(int u,int ft){
	if(!e[head[u]].nxt)return dp[u]=a[u],siz[u]=1,void();
	LL sum=0;siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==ft)continue;
		fa[v]=u,dfs1(v,u),sum+=dp[v],siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
	dp[u]=min(sum,a[u]);
}
void dfs2(int u,int tp){
	top[u]=tp,dfn[u]=++tmr,rev[tmr]=u,ed[tp]=tmr;
	mat[u][0][0]=0,mat[u][0][1]=a[u],
	mat[u][1][0]=0,mat[u][1][1]=0;
	if(!son[u])return mat[u][0][0]=inf,void();
	dfs2(son[u],tp);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v),mat[u][0][0]+=dp[v];
	}
}
#define lc (p<<1)
#define rc (p<<1|1)
void pushup(int p){val[p]=val[lc]*val[rc];}
void build(int l,int r,int p=1){
	if(l==r)return val[p]=mat[rev[l]],void();
	int mid=(l+r)>>1;
	build(l,mid,lc),build(mid+1,r,rc);
	pushup(p);
}
Matrix query(int ql,int qr,int l=1,int r=n,int p=1){
	if(ql<=l&&r<=qr)return val[p];
	int mid=(l+r)>>1;
	if(qr<=mid)return query(ql,qr,l,mid,lc);
	if(mid<ql)return query(ql,qr,mid+1,r,rc);
	return query(ql,qr,l,mid,lc)*query(ql,qr,mid+1,r,rc);
}
void change(int pos,int l=1,int r=n,int p=1){
	if(l==r)return val[p]=mat[rev[pos]],void();
	int mid=(l+r)>>1;
	if(pos<=mid)change(pos,l,mid,lc);
	else change(pos,mid+1,r,rc);
	pushup(p);
}
void update(int x,int v){
	mat[x][0][1]+=v,a[x]+=v;
	while(x){
		Matrix lst=query(dfn[top[x]],ed[top[x]]);
		change(dfn[x]);
		Matrix now=query(dfn[top[x]],ed[top[x]]);
		x=fa[top[x]];
		mat[x][0][0]+=min(now[0][0],now[0][1])-min(lst[0][0],lst[0][1]);
	}
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		addedge(x,y),addedge(y,x);
	}
	dfs1(1,0),dfs2(1,1),build(1,n);
	for(int m=read();m;--m){
		int opt=rdc(),x=read();
		if(opt){
			Matrix t=query(dfn[x],ed[top[x]]);
			printf("%lld\n",min(t[0][0],t[0][1]));
		}
		else update(x,read());
	}
	return 0;
}