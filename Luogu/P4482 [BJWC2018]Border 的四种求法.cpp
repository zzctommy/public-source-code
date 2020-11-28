#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}

#define N 200005
const int inf=0x3f3f3f3f;
char str[N];
int n,numq,root[N<<1];
struct QUE{
	int l,r,id;
	QUE(){l=r=id=0;}
	QUE(int l_,int r_,int d_){l=l_,r=r_,id=d_;}
};
vector<QUE>q[N<<1];
int ans[N];

namespace SAM{
#define S (N<<1)
int link[S],trans[S][26],rev[S],mxlen[S],tot=1,to[N];
int extend(int c,int lst,int id){
	int p=lst,np=++tot;mxlen[np]=mxlen[p]+1,rev[np]=id,to[id]=np;
	for(;p&&!trans[p][c];p=link[p])trans[p][c]=np;
	if(!p)link[np]=1;
	else{
		int q=trans[p][c];
		if(mxlen[p]+1==mxlen[q])link[np]=q;
		else{
			int nq=++tot;mxlen[nq]=mxlen[p]+1;
			for(int i=0;i<26;++i)trans[nq][i]=trans[q][i];
			link[nq]=link[q],link[q]=link[np]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
		}
	}
	return np;
}
void insert(char*str){
	int n=strlen(str);
	for(int i=0,lst=1;i<n;++i)lst=extend(str[i]-'a',lst,i+1);
}
#undef S
	
}

namespace seg{

#define T (N<<2)
#define lc (p<<1)
#define rc (p<<1|1)
int miv[T],tot;
void init(){memset(miv,0x3f,sizeof(miv));}
void pushup(int p){miv[p]=min(miv[lc],miv[rc]);}
void update(int pos,int k,int l=1,int r=n,int p=1){
	if(l==r)return miv[p]=k,void();
	int mid=(l+r)>>1;
	if(pos<=mid)update(pos,k,l,mid,lc);
	else update(pos,k,mid+1,r,rc);
	pushup(p);
}
int query(int ql,int qr,int l=1,int r=n,int p=1){
	if(miv[p]>=ql)return 0;
	if(l==r)return miv[p]<ql?l:0;
	int mid=(l+r)>>1,res;
	if(qr>mid){
		res=query(ql,qr,mid+1,r,rc);
		if(res)return res;
	}
	if(ql<=mid)return query(ql,qr,l,mid,lc);
	return 0;
}
#undef T
#undef lc
#undef rc

}

namespace mgt{

#define T ((N<<1)*40)
int ls[T],rs[T],val[T],tot;
void pushup(int p){
	val[p]=val[ls[p]]+val[rs[p]];
}
void update(int&p,int pos,int k,int l=1,int r=n){
	if(!p)p=++tot;
	if(l==r)return val[p]+=k,void();
	int mid=(l+r)>>1;
	if(pos<=mid)update(ls[p],pos,k,l,mid);
	else update(rs[p],pos,k,mid+1,r);
	pushup(p); 
}
int query(int p,int ql,int qr,int l=1,int r=n){
	if(!val[p])return 0;
	if(l==r)return l;
	int mid=(l+r)>>1,res;
	if(qr>mid){
		res=query(rs[p],ql,qr,mid+1,r);
		if(res)return res;
	}
	if(ql<=mid)return query(ls[p],ql,qr,l,mid);
	return 0;
}
int merge(int x,int y,int l=1,int r=n){
	if(!x||!y)return x|y;
	if(l==r)return val[x]+=val[y],x;
	int mid=(l+r)>>1,p=++tot;
	ls[p]=merge(ls[x],ls[y],l,mid);
	rs[p]=merge(rs[x],rs[y],mid+1,r);
	return pushup(p),p;
}
#undef T
	
}

namespace Tree{
	
#define T (N<<1)
int hed[T],et;
int top[T],fa[T],son[T],siz[T],dep[T];
struct edge{int nx,to;}e[T<<1];
void addedge(int u,int v){e[++et].nx=hed[u],e[et].to=v,hed[u]=et;}
void dfs1(int u,int ft){
	siz[u]=1,fa[u]=ft,dep[u]=dep[ft]+1;
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		dfs1(v,u),siz[u]+=siz[v],root[u]=mgt::merge(root[u],root[v]);
		if(siz[v]>siz[son[u]])son[u]=v;
	}
	if(SAM::rev[u])mgt::update(root[u],SAM::rev[u],1);
}
void dfs2(int u,int tp){
	top[u]=tp;
	if(son[u])dfs2(son[u],tp);
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
void init(){
	for(int i=1;i<=SAM::tot;++i)addedge(SAM::link[i],i);
	dfs1(1,0),dfs2(1,1),seg::init();
}
void upd(int u,int x){
	if(SAM::rev[u])seg::update(SAM::rev[u],x<inf?SAM::rev[u]-x:inf);
	for(int i=hed[u];i;i=e[i].nx)upd(e[i].to,x);
}
void dfs(int rt){
	for(int u=rt;u;u=son[u]){
		if(SAM::rev[u])seg::update(SAM::rev[u],SAM::rev[u]-SAM::mxlen[u]);
		for(int i=hed[u];i;i=e[i].nx)if(e[i].to!=son[u])upd(e[i].to,SAM::mxlen[u]);
		for(vector<QUE>::iterator i=q[u].begin();i!=q[u].end();++i){
			int t=mgt::query(root[u],i->l,min(i->l+SAM::mxlen[u]-1,i->r-1));
			if(t)ckmax(ans[i->id],t-i->l+1);
			t=seg::query(i->l,i->r-1);
			if(t)ckmax(ans[i->id],t-i->l+1);
		}
	}
	for(int u=rt;u;u=son[u]){
		if(SAM::rev[u])seg::update(SAM::rev[u],inf);
		for(int i=hed[u];i;i=e[i].nx)if(e[i].to!=son[u])upd(e[i].to,inf);
	}
	for(int u=rt;u;u=son[u])
		for(int i=hed[u];i;i=e[i].nx)
			if(e[i].to!=son[u])dfs(e[i].to);
}

#undef T
	
}

signed main(){
	scanf("%s%d",str,&numq),n=strlen(str),SAM::insert(str);
	Tree::init();
	for(int i=1;i<=numq;++i){
		int l=read(),r=read(),now=SAM::to[r];
		if(l==r){ans[i]=0;continue;}
		while(now)q[now].pb(QUE(l,r,i)),now=Tree::fa[Tree::top[now]];
	}
	Tree::dfs(1);
	for(int i=1;i<=numq;++i)printf("%d\n",ans[i]);
	return 0;
}