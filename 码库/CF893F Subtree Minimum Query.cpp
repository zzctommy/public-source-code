// Problem: F. Subtree Minimum Query
// Contest: Codeforces - Educational Codeforces Round 33 (Rated for Div. 2)
// URL: https://codeforces.com/contest/893/problem/F
// Memory Limit: 512 MB
// Time Limit: 6000 ms

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

const int N=100005;
const int T=N*60;
const int inf=0x3f3f3f3f;
vector<int>g[N];
int n,q,dep[N],las,rt[N],a[N],r;
int ls[T],rs[T],val[T],tot;
void pushup(int p){
	val[p]=min(val[ls[p]],val[rs[p]]);
}
void update(int&p,int pos,int k,int l=1,int r=n){
	if(!p)p=++tot;
	if(l==r)return val[p]=k,void();
	int mid=(l+r)>>1;
	if(pos<=mid)update(ls[p],pos,k,l,mid);
	else update(rs[p],pos,k,mid+1,r);
	pushup(p);
}
int query(int p,int ql,int qr,int l=1,int r=n){
	if(!p)return inf;
	if(ql<=l&&r<=qr)return val[p];
	int mid=(l+r)>>1,res=inf;
	if(ql<=mid)ckmin(res,query(ls[p],ql,qr,l,mid));
	if(mid<qr)ckmin(res,query(rs[p],ql,qr,mid+1,r));
	return res;
}
int merge(int x,int y,int l,int r){
	if(!x||!y)return x|y;
	if(l==r)return val[++tot]=min(val[x],val[y]),tot;
	int mid=(l+r)>>1,p=++tot;
	ls[p]=merge(ls[x],ls[y],l,mid);
	rs[p]=merge(rs[x],rs[y],mid+1,r);
	return pushup(p),p;
}
void dfs(int u,int ft){
	dep[u]=dep[ft]+1;
	update(rt[u],dep[u],a[u]);
	for(int v:g[u]){
		if(v==ft)continue;
		dfs(v,u);
		rt[u]=merge(rt[u],rt[v],1,n);
	}
}
signed main(){
	n=read(),r=read();
	val[0]=inf;
	rep(i,1,n)a[i]=read();
	rep(i,2,n){
		int x=read(),y=read();
		g[x].pb(y),g[y].pb(x);
	}
	dfs(r,0);
	q=read();
	rep(t,1,q){
		int x=read(),y=read();
		x=(las+x)%n+1,y=(las+y)%n;
		printf("%d\n",las=query(rt[x],dep[x],dep[x]+y));
	}
}