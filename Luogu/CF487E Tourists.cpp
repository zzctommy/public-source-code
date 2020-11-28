//Orz cyn2006
#include<bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long LL;
#define pb(x) push_back(x)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 100005
int n,m,q,w[N<<1],tot;
namespace Tree{

#define T (N<<1)
#define S (T<<2)
#define inf 1000000007

struct egde{int nxt,to;}e[T<<1];
int num_edge,head[T];
multiset<int>s[T];
int dfn[T],tmr,rev[T],fa[T],top[T],son[T],siz[T],dep[T];
int val[S];

void addedge(int fr,int to){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
void dfs1(int u,int ft){
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==ft)continue;
		fa[v]=u,dep[v]=dep[u]+1,dfs1(v,u),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp){
	rev[dfn[u]=++tmr]=u,top[u]=tp;
	if(son[u])dfs2(son[u],tp);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
#define lc (p<<1)
#define rc (p<<1|1)
void pushup(int p){val[p]=min(val[lc],val[rc]);}
void build(int l=1,int r=tot,int p=1){
	if(l==r)return val[p]=w[rev[l]],void();
	int mid=(l+r)>>1;
	build(l,mid,lc),build(mid+1,r,rc);
	pushup(p);
}
void change(int pos,int k,int l=1,int r=tot,int p=1){
	if(l==r)return val[p]=k,void();
	int mid=(l+r)>>1;
	if(pos<=mid)change(pos,k,l,mid,lc);
	else change(pos,k,mid+1,r,rc);
	pushup(p);
}
int query_min(int ql,int qr,int l=1,int r=tot,int p=1){
	if(ql<=l&&r<=qr)return val[p];
	int mid=(l+r)>>1,res=inf;
	if(ql<=mid)res=min(res,query_min(ql,qr,l,mid,lc));
	if(mid<qr)res=min(res,query_min(ql,qr,mid+1,r,rc));
	return res;
}
int ask_min(int x,int y){
	int res=inf;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
		res=min(res,query_min(dfn[top[x]],dfn[x])),x=fa[top[x]];
	}
	if(dfn[x]>dfn[y])x^=y^=x^=y;
	return min(res,query_min(dfn[x],dfn[y]));
}
void modify(int x,int y){
	if(fa[x]>n){
		s[fa[x]].erase(s[fa[x]].find(w[x]));
		s[fa[x]].insert(y);
		if(w[fa[x]]!=*s[fa[x]].begin()){
			w[fa[x]]=*s[fa[x]].begin();
			change(dfn[fa[x]],w[fa[x]]);
		}
	}
	change(dfn[x],w[x]=y);
}
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int query(int x,int y){
	int res=ask_min(x,y),lca=LCA(x,y);
	if(lca>n)res=min(res,w[fa[lca]]);
	return res;
}
void init(){
	dfs1(1,0),dfs2(1,1);
	for(int i=1;i<=n;++i)s[fa[i]].insert(w[i]);
	for(int i=n+1;i<=tot;++i)w[i]=*s[i].begin();
	build();
}

}

namespace cst{


int dfn[N],tmr,low[N],stk[N],top;
struct egde{int nxt,to;}e[N<<1];
int num_edge,head[N];

void addedge(int fr,int to){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
void tarjan(int u){
	dfn[u]=low[u]=++tmr,stk[++top]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tarjan(v),low[u]=min(low[u],low[v]);
			if(dfn[u]==low[v]){
				++tot;
				Tree::addedge(tot,u),Tree::addedge(u,tot);
				while(stk[top+1]!=v){
					Tree::addedge(tot,stk[top]),Tree::addedge(stk[top],tot),--top;
				}
			}
		}else low[u]=min(low[u],dfn[v]);
	}
}

}
signed main(){
	tot=n=read(),m=read(),q=read();
	for(int i=1;i<=n;++i)w[i]=read();
	for(int i=1;i<=m;++i){
		int x=read(),y=read();
		cst::addedge(x,y),cst::addedge(y,x);
	}
	cst::tarjan(1),Tree::init();
	while(q--){
		char ch=getchar();
		while(ch!='C'&&ch!='A')ch=getchar();
		int x=read(),y=read();
		if(ch=='C')Tree::modify(x,y);
		else printf("%d\n",Tree::query(x,y));
	}
	return 0;
}