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
	while(!isdigit(ch)) {if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?x:-x;
}
const int N=400005;
const int M=N<<1;
const int T=N<<2;
const int inf=0x3f3f3f3f;
int n,cnt,a[M],FR[N],TO[N],V[N],MD[N];
int fa[M],top[M],dfn[M],rev[M],tmr,siz[M],son[M],dep[M];
int mxv[T],miv[T],sum[T],tag[T];
struct edge{
	int nxt,to;
}e[M<<1];
int head[M],num_edge;
void addedge(int fr,int to){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
void adde(int fr,int to){addedge(fr,to),addedge(to,fr);}
void dfs1(int u,int ft){
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==ft)continue;
		dep[v]=dep[u]+1,dfs1(v,u),siz[u]+=siz[v],fa[v]=u;
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp){
	dfn[u]=++tmr,rev[tmr]=u,top[u]=tp;
	if(son[u])dfs2(son[u],tp);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa[u]&&v!=son[u])dfs2(v,v);
	}
}
#define lc (p<<1)
#define rc (p<<1|1)
void pushup(int p){
	mxv[p]=max(mxv[lc],mxv[rc]);
	miv[p]=min(miv[lc],miv[rc]);
	sum[p]=sum[lc]+sum[rc];
}
void build(int l,int r,int p=1){
	sum[p]=0,miv[p]=inf,mxv[p]=-inf;
	if(l==r){
		if(a[rev[l]]!=inf)sum[p]=miv[p]=mxv[p]=a[rev[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,lc),build(mid+1,r,rc);
	pushup(p);
}
void addtag(int p){sum[p]=-sum[p],swap(mxv[p],miv[p]),mxv[p]=-mxv[p],miv[p]=-miv[p],tag[p]^=1;}
void pushdown(int p){if(tag[p])addtag(lc),addtag(rc),tag[p]=0;}
void update(int ql,int qr,int l=1,int r=cnt,int p=1){
	if(ql<=l&&r<=qr)return addtag(p),void();
	pushdown(p);
	int mid=(l+r)>>1;
	if(mid<ql)update(ql,qr,mid+1,r,rc);
	else if(qr<=mid)update(ql,qr,l,mid,lc);
	else update(ql,qr,l,mid,lc),update(ql,qr,mid+1,r,rc);
	pushup(p);
}
void change(int pos,int k,int l=1,int r=cnt,int p=1){
	if(l==r)return sum[p]=miv[p]=mxv[p]=k,void();
	pushdown(p);
	int mid=(l+r)>>1;
	if(pos<=mid)change(pos,k,l,mid,lc);
	else change(pos,k,mid+1,r,rc);
	pushup(p);
}
int query_sum(int ql,int qr,int l=1,int r=cnt,int p=1){
	if(ql<=l&&r<=qr)return sum[p];
	pushdown(p);
	int mid=(l+r)>>1;
	if(mid<ql)return query_sum(ql,qr,mid+1,r,rc);
	else if(qr<=mid)return query_sum(ql,qr,l,mid,lc);
	else return query_sum(ql,qr,l,mid,lc)+query_sum(ql,qr,mid+1,r,rc);
}
int query_max(int ql,int qr,int l=1,int r=cnt,int p=1){
	if(ql<=l&&r<=qr)return mxv[p];
	pushdown(p);
	int mid=(l+r)>>1;
	if(mid<ql)return query_max(ql,qr,mid+1,r,rc);
	else if(qr<=mid)return query_max(ql,qr,l,mid,lc);
	else return max(query_max(ql,qr,l,mid,lc),query_max(ql,qr,mid+1,r,rc));
}
int query_min(int ql,int qr,int l=1,int r=cnt,int p=1){
	if(ql<=l&&r<=qr)return miv[p];
	pushdown(p);
	int mid=(l+r)>>1;
	if(mid<ql)return query_min(ql,qr,mid+1,r,rc);
	else if(qr<=mid)return query_min(ql,qr,l,mid,lc);
	else return min(query_min(ql,qr,l,mid,lc),query_min(ql,qr,mid+1,r,rc));
}
int ask_sum(int x,int y){
	int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
		res+=query_sum(dfn[top[x]],dfn[x]),x=fa[top[x]];
//		std::cout<<dfn[top[x]]<<' '<<dfn[x]<<' '<<query_sum(dfn[top[x]],dfn[x])<<'\n';
	}
	if(dfn[x]>dfn[y])x^=y^=x^=y;
//	std::cout<<dfn[x]<<' '<<dfn[y]<<' '<<query_sum(dfn[x],dfn[y])<<'\n';
	return res+query_sum(dfn[x],dfn[y]);
}
int ask_max(int x,int y){
	int res=-inf;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
		res=max(res,query_max(dfn[top[x]],dfn[x])),x=fa[top[x]];
	}
	if(dfn[x]>dfn[y])x^=y^=x^=y;
	return max(res,query_max(dfn[x],dfn[y]));
}
int ask_min(int x,int y){
//	cout<<x<<' '<<y<<endl;
	int res=inf;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
		res=min(res,query_min(dfn[top[x]],dfn[x])),x=fa[top[x]];
//		cout<<dfn[top[x]]<<' '<<dfn[x]<<' '<<query_min(dfn[top[x]],dfn[x])<<endl;
	}
	if(dfn[x]>dfn[y])x^=y^=x^=y;
//	cout<<dfn[x]<<' '<<dfn[y]<<' '<<query_min(dfn[x],dfn[y])<<endl;
	return min(res,query_min(dfn[x],dfn[y]));
}
void upd(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
		update(dfn[top[x]],dfn[x]),x=fa[top[x]];
	}
	if(dfn[x]>dfn[y])x^=y^=x^=y;
	update(dfn[x],dfn[y]);
}
signed main(){
	n=read(),cnt=n;
	memset(a,0x3f,sizeof(a));
	for(int i=1;i<n;++i){
		FR[i]=read()+1,TO[i]=read()+1,V[i]=read();
		MD[i]=++cnt,adde(FR[i],MD[i]),a[MD[i]]=V[i],adde(MD[i],TO[i]);
	}
	dfs1(1,0),dfs2(1,1),build(1,cnt);
	char opt[10];
	for(int q=read();q;--q){
		scanf("%s",opt);int x=read()+1,y=read()+1;
		if(opt[0]=='C')change(dfn[MD[--x]],--y);
		else if(opt[0]=='N')upd(x,y);
		else if(opt[0]=='S')printf("%d\n",ask_sum(x,y));
		else if(opt[1]=='A')printf("%d\n",ask_max(x,y));
		else if(opt[1]=='I')printf("%d\n",ask_min(x,y));
		else puts("cynAKIOI!!!");
	}
	return 0;
}