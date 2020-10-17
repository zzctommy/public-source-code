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
const int N=100005;
const int M=N<<2;
const LL inf=1e12;
int n,m;
LL p[N];
int siz[N],dfn[N],tmr,son[N],fa[N],top[N],rev[N],ed[N],f[N][2];
char cynAKIOI[114514];
struct edge{
	int nxt,to;
}e[N<<1];
int head[N],num_edge;
void addedge(int fr,int to){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
struct Matrix{
	LL p[2][2];
	Matrix(){p[0][0]=p[0][1]=p[1][0]=p[1][1]=-inf;}
	LL*operator[](const int&k){return p[k];}
	Matrix operator * (const Matrix&b){
		Matrix res;
//		for(int i=0;i<2;++i)
//			for(int j=0;j<2;++j)
//				for(int k=0;k<2;++k)
//					res.p[i][j]=max(res.p[i][j],p[i][k]+b.p[k][j]);
		res[0][0]=max(p[0][0]+b.p[0][0],p[0][1]+b.p[1][0]);
		res[0][1]=max(p[0][0]+b.p[0][1],p[0][1]+b.p[1][1]);
		res[1][0]=max(p[1][0]+b.p[0][0],p[1][1]+b.p[1][0]);
		res[1][1]=max(p[1][0]+b.p[0][1],p[1][1]+b.p[1][1]);
		return res;
	}
}mat[N],val[M];
void dfs1(int u,int ft){
	siz[u]=1,f[u][1]=p[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==ft)continue;
		fa[v]=u,dfs1(v,u),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
		f[u][0]+=max(f[v][0],f[v][1]);
		f[u][1]+=f[v][0];
	}
}
void dfs2(int u,int tp){
	top[u]=tp,dfn[u]=++tmr,rev[tmr]=u,ed[tp]=tmr;
	if(son[u])dfs2(son[u],tp);
	LL g[2];g[0]=0,g[1]=p[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==son[u]||v==fa[u])continue;
		dfs2(v,v);
		g[0]+=max(f[v][0],f[v][1]);
		g[1]+=f[v][0];
	}
	mat[u][0][0]=g[0],mat[u][0][1]=g[0];
	mat[u][1][0]=g[1],mat[u][1][1]=-inf;
}
#define lc (p<<1)
#define rc (p<<1|1)
void pushup(int p){val[p]=val[lc]*val[rc];}
void build(int l,int r,int p){
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
	if(l==r)return val[p]=mat[rev[l]],void();
	int mid=(l+r)>>1;
	if(pos<=mid)change(pos,l,mid,lc);
	else change(pos,mid+1,r,rc);
	pushup(p);
}
void update(int x,LL v){
	mat[x][1][0]+=v,p[x]+=v;
	while(x){
		Matrix lst=query(dfn[top[x]],ed[top[x]]);
		change(dfn[x]);
		Matrix now=query(dfn[top[x]],ed[top[x]]);
		x=fa[top[x]];
		mat[x][0][0]+=max(now[0][0],now[1][0])-max(lst[0][0],lst[1][0]);
		mat[x][0][1]=mat[x][0][0];
		mat[x][1][0]+=now[0][0]-lst[0][0];
	}
}
signed main(){
	n=read(),m=read(),scanf("%s",cynAKIOI);
	for(int i=1;i<=n;++i)p[0]+=(p[i]=read());
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		addedge(x,y),addedge(y,x);
	}
	dfs1(1,0),dfs2(1,1),build(1,n,1);
	while(m--){
		int a=read(),x=read(),b=read(),y=read();
		LL ad1=x?-inf:inf,out1=x?0:inf;
		LL ad2=y?-inf:inf,out2=y?0:inf;
		update(a,ad1),update(b,ad2);
		Matrix res=query(dfn[1],ed[1]);
		LL out=p[0]-max(res[0][0],res[1][0])+out1+out2;
		out<inf?printf("%lld\n",out):puts("-1");
		update(a,-ad1),update(b,-ad2);
	}
	return 0;
}