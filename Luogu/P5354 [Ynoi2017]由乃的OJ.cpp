#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
inline unsigned long long readull(){
	unsigned long long x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return x;
}
const int N=100005;
int n,m,k;
struct node{
	unsigned long long a[2][2];
	node(){a[0][0]=a[1][0]=0,a[0][1]=a[1][1]=-1;}
	void init(int opt,unsigned long long x){
		if(opt==1)a[0][0]=0,a[0][1]=x,a[1][0]=0,a[1][1]=x;
		else if(opt==2)a[0][0]=x,a[0][1]=-1,a[1][0]=x,a[1][1]=-1;
		else if(opt==3)a[0][0]=x,a[0][1]=(-1)^x,a[1][0]=x,a[1][1]=(-1)^x;
	}
	friend node operator + (const node&a,const node&b){
		node res;
		res.a[0][0]=(a.a[0][0]&b.a[0][1])|((~a.a[0][0])&b.a[0][0]);
		res.a[0][1]=(a.a[0][1]&b.a[0][1])|((~a.a[0][1])&b.a[0][0]);
		res.a[1][0]=(b.a[1][0]&a.a[1][1])|((~b.a[1][0])&a.a[1][0]);
		res.a[1][1]=(b.a[1][1]&a.a[1][1])|((~b.a[1][1])&a.a[1][0]);
		return res;
	}
	node inv(){
		node res=*this;
		swap(res.a[0][0],res.a[1][0]),swap(res.a[0][1],res.a[1][1]);
		return res;
	}
}a[N],val[N<<2];
int top[N],fa[N],rev[N],dfn[N],son[N],siz[N],dep[N],tmr;
int et,hed[N];
struct edge{int nx,to;}e[N<<1];
void adde(int u,int v){e[++et].nx=hed[u],e[et].to=v,hed[u]=et;}
void dfs1(int u,int ft){
	siz[u]=1,dep[u]=dep[ft]+1;
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		dfs1(v,u),fa[v]=u,siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp){
	rev[dfn[u]=++tmr]=u,top[u]=tp;
	if(son[u])dfs2(son[u],tp);
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
#define lc (p<<1)
#define rc (p<<1|1)
void pushup(int p){val[p]=val[lc]+val[rc];}
void build(int l=1,int r=n,int p=1){
	if(l==r)return val[p]=a[rev[l]],void();
	int mid=(l+r)>>1;
	build(l,mid,lc),build(mid+1,r,rc);
	pushup(p);
}
node query(int ql,int qr,int l=1,int r=n,int p=1){
	if(ql<=l&&r<=qr)return val[p];
	int mid=(l+r)>>1;
	if(qr<=mid)return query(ql,qr,l,mid,lc);
	if(mid<ql)return query(ql,qr,mid+1,r,rc);
	return query(ql,qr,l,mid,lc)+query(ql,qr,mid+1,r,rc);
}
void change(int pos,int l=1,int r=n,int p=1){
	if(l==r)return val[p]=a[rev[l]],void();
	int mid=(l+r)>>1;
	if(pos<=mid)change(pos,l,mid,lc);
	else change(pos,mid+1,r,rc);
	pushup(p);
}
node ask(int x,int y){
	node res1,res2;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])res1=res1+query(dfn[top[x]],dfn[x]).inv(),x=fa[top[x]];
		else res2=query(dfn[top[y]],dfn[y])+res2,y=fa[top[y]];
	}
	if(dfn[x]<dfn[y])res2=query(dfn[x],dfn[y])+res2;
	else res1=res1+query(dfn[y],dfn[x]).inv();
	return res1+res2;
}
signed main(){
	n=read(),m=read(),k=read();
	rep(i,1,n){
		int opt=read();unsigned long long x=readull();
		a[i].init(opt,x);
	}
	rep(i,2,n){
		int x=read(),y=read();
		adde(x,y),adde(y,x);
	}
	dfs1(1,0),dfs2(1,1),build();
	while(m--){
		int opt=read(),x=read(),y=read();
		unsigned long long z=readull(),res=0;
		if(opt==1){
			node p=ask(x,y);
			// cerr<<"p:"<<p.a[0][0]<<' '<<p.a[0][1]<<'\n';
			per(i,k-1,0){
				unsigned long long tmp=1ull<<i;
				if(p.a[0][0]&tmp)res|=tmp;
				else if(p.a[0][1]&tmp&&z>=tmp)res|=tmp,z-=tmp;
			}
			printf("%llu\n",res);
		}else a[x].init(y,z),change(dfn[x]);
	}
	return 0;
}