#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef long double db;
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
const int N=80005;
const int M=N<<1;
int n,m,nq,nu,t[N],lsh[M],len,bel[M],tmr,S,ans[N];
int siz[N],fa[N],top[N],son[N],dep[N],st[N],ed[N],rev[M];
bool used[M];
struct node{int k,a,b;}o[N];
struct que{
	int l,r,id,lca,pre,k;
	que(){l=r=id=lca=pre=k=0;}
	inline bool operator < (const que&t)const{return bel[l]!=bel[t.l]?l<t.l:bel[r]!=bel[t.r]?r<t.r:pre<t.pre;}
}q[N];
struct upd{int x,y,id;}u[N];
int hed[N],et;
struct edge{int nx,to;}e[M];
void adde(int u,int v){e[++et].nx=hed[u],e[et].to=v,hed[u]=et;}
void dfs1(int u,int ft){
	siz[u]=1,dep[u]=dep[ft]+1;
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		fa[v]=u,dfs1(v,u),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp){
	top[u]=tp,rev[st[u]=++tmr]=u;
	if(son[u])dfs2(son[u],tp);
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
	rev[ed[u]=++tmr]=u;
}
int LCA(int x,int y){
	while(top[x]!=top[y])dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
	return dep[x]<dep[y]?x:y;
}
namespace BLO{
int bel[M],sum[M],cnt[M],S,L[M],R[M],num,added;
void init(){
	S=sqrt(len),num=(len-1)/S+1;
	rep(i,1,num)L[i]=R[i-1]+1,R[i]=i*S;R[num]=len;
	rep(i,1,num)rep(j,L[i],R[i])bel[j]=i;
}
void update(int x,int d){
	cnt[x]+=d,sum[bel[x]]+=d,added+=d;
}
int query(int k){
	//cerr<<added<<'\n';
	//rep(i,1,len)cerr<<cnt[i]<<' ';cerr<<'\n';
	if(k>added)return -1;
	int it=num;
	while(k>sum[it])k-=sum[it--];
	per(i,R[it],L[it]){
		if(k<=cnt[i])return i;
		k-=cnt[i];
	}
}
}
void flip(int x){
	used[x]?BLO::update(t[x],-1):BLO::update(t[x],1);used[x]^=1;
}
void modify(int x,int i){
	if(used[u[x].x])BLO::update(t[u[x].x],-1),BLO::update(u[x].y,1);
	swap(t[u[x].x],u[x].y);
}
signed main(){
	n=read(),m=read();
	rep(i,1,n)t[i]=lsh[++len]=read();
	rep(i,2,n){
		int x=read(),y=read();
		adde(x,y),adde(y,x);
	}
	dfs1(1,0),dfs2(1,0);
	//rep(i,1,n)cerr<<st[i]<<' ';cerr<<'\n';
	//rep(i,1,n)cerr<<ed[i]<<' ';cerr<<'\n';
	rep(i,1,m){
		o[i].k=read(),o[i].a=read(),o[i].b=read();
		if(!o[i].k)lsh[++len]=o[i].b;
	}
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	rep(i,1,n)t[i]=lower_bound(lsh+1,lsh+len+1,t[i])-lsh;
	rep(i,1,m)if(!o[i].k)o[i].b=lower_bound(lsh+1,lsh+len+1,o[i].b)-lsh;
	rep(i,1,m){
		if(!o[i].k)++nu,u[nu].x=o[i].a,u[nu].y=o[i].b;
		else{
			int x=o[i].a,y=o[i].b,lca=LCA(x,y);
			++nq,q[nq].id=nq,q[nq].pre=nu,q[nq].k=o[i].k;
			if(st[x]>st[y])x^=y^=x^=y;
			if(lca==x)q[nq].l=st[x],q[nq].r=st[y],q[nq].lca=0;
			else q[nq].l=ed[x],q[nq].r=st[y],q[nq].lca=lca;
		}
	}
	S=pow(tmr,0.666);rep(i,1,tmr)bel[i]=(i-1)/S+1;
	sort(q+1,q+nq+1);
	BLO::init();
	for(int i=1,l=1,r=0,nd=0;i<=nq;++i){
		while(l>q[i].l)flip(rev[--l]);
		while(r<q[i].r)flip(rev[++r]);
		while(l<q[i].l)flip(rev[l++]);
		while(r>q[i].r)flip(rev[r--]);
		while(nd<q[i].pre)modify(++nd,i);
		while(nd>q[i].pre)modify(nd--,i);
		if(q[i].lca)flip(q[i].lca);
		ans[q[i].id]=BLO::query(q[i].k);
		if(q[i].lca)flip(q[i].lca);
	}
	rep(i,1,nq){
		if(~ans[i])printf("%d\n",lsh[ans[i]]);
		else puts("invalid request!");
	}
	return 0;
}
/*
5 5
5 1 2 3 4
3 1
2 1
4 3
5 3
2 4 5
0 1 2
2 2 3
2 1 4
3 3 5

*/