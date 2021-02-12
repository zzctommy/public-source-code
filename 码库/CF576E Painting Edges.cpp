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
const int K=52;
const int N=500005;
const int T=N<<2;
int n,m,k,q,a[N],b[N],e[N],c[N],lst[N],fir[N],ans[N],ed[N];
struct DSU{
	vector<int>stk;
	int F[N<<1],siz[N<<1],tim;
	void init(const int&n){rep(i,1,n)F[i]=i,siz[i]=1;}
	inline int anc(int x){while(x!=F[x])x=F[x];return x;}
	void merge(int x,int y){
		x=anc(x),y=anc(y);
		if(x==y)return;
		if(siz[x]<siz[y])x^=y^=x^=y;
		siz[x]+=siz[y],F[y]=x,stk.pb(y);
	}
	void undo(){
		int x=stk.back();stk.pop_back();
		siz[F[x]]-=siz[x],F[x]=x;
	}
}dsu[K];
vector<pair<int,int> >upd[T];
#define lc (p<<1)
#define rc (p<<1|1)
void update(int ql,int qr,pair<int,int>d,int l=1,int r=q,int p=1){
	if(ql>qr)return;
	// cerr<<"update:"<<ql<<' '<<qr<<' '<<d.fi<<' '<<d.se<<' '<<l<<' '<<r<<' '<<p<<'\n';
	if(ql<=l&&r<=qr)return upd[p].pb(d),void();
	int mid=(l+r)>>1;
	if(ql<=mid)update(ql,qr,d,l,mid,lc);
	if(mid<qr)update(ql,qr,d,mid+1,r,rc);
}
void solve(int l,int r,int p){
	// cerr<<"solve:"<<l<<' '<<r<<'\n';
	int nwsz[K],mid=(l+r)>>1;
	rep(i,1,k)nwsz[i]=sz(dsu[i].stk);
	for(pair<int,int>i:upd[p]){
		int id=i.fi,cc=i.se,x=a[e[id]],y=b[e[id]];
		dsu[cc].merge(x+n,y),dsu[cc].merge(x,y+n);
	}
	if(l==r){
		int x=a[e[l]],y=b[e[l]],cc;
		if(dsu[c[l]].anc(x)==dsu[c[l]].anc(y))cc=fir[e[l]],ans[l]=0;
		else cc=c[l],fir[e[l]]=c[l],ans[l]=1;
		if(cc)update(l+1,ed[l],mkp(l,cc));
	}else solve(l,mid,lc),solve(mid+1,r,rc);
	rep(i,1,k)while(sz(dsu[i].stk)>nwsz[i])dsu[i].undo();
}
signed main(){
	n=read(),m=read(),k=read(),q=read();
	rep(i,1,m)a[i]=read(),b[i]=read();
	rep(i,1,q){
		e[i]=read(),c[i]=read();
		if(lst[e[i]])ed[lst[e[i]]]=i-1;
		lst[e[i]]=i;
	}
	rep(i,1,m)if(lst[i]&&lst[i]<q)ed[lst[i]]=q;
	rep(i,1,k)dsu[i].init(n<<1);
	solve(1,q,1);
	rep(i,1,q)puts(ans[i]?"YES":"NO");
}