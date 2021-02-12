#include"plants.h"
#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define sz(v) (int)(v).size()
template<class T>inline bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>inline bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
typedef long long LL;

const int N=200005;
const int T=N<<2;
const int inf=0x3f3f3f3f;
int n,a[N],tpn[N],tpo,len;
int L[20][N],R[20][N];
LL dl[20][N],dr[20][N];
vector<int>v0;

namespace sg1{
int miv[T],tag[T],id[T];
#define lc (p<<1)
#define rc (p<<1|1)
void pushup(int p){
	miv[p]=inf,id[p]=0;
	if(ckmin(miv[p],miv[lc]))id[p]=id[lc];
	if(ckmin(miv[p],miv[rc]))id[p]=id[rc];
}
void build(int l,int r,int p,int*a){
	tag[p]=0,miv[p]=inf;
	if(l==r)return miv[p]=a[l],id[p]=l,void();
	int mid=(l+r)>>1;
	build(l,mid,lc,a),build(mid+1,r,rc,a);
	pushup(p);
}
void pushdown(int p){
	if(tag[p]){
		tag[lc]+=tag[p],miv[lc]+=tag[p];
		tag[rc]+=tag[p],miv[rc]+=tag[p];
		tag[p]=0;
	}
}
void get0(int p,int l,int r){
	if(l==r)return v0.pb(l),void();
	pushdown(p);
	int mid=(l+r)>>1;
	if(!miv[lc])get0(lc,l,mid);
	if(!miv[rc])get0(rc,mid+1,r);
}
void update(int ql,int qr,int d,int l=1,int r=n,int p=1){
	if(ql>qr)return;
	if(ql<=l&&r<=qr){
		miv[p]+=d,tag[p]+=d;
		if(!miv[p])get0(p,l,r);
		return;
	}
	pushdown(p);
	int mid=(l+r)>>1;
	if(ql<=mid)update(ql,qr,d,l,mid,lc);
	if(mid<qr)update(ql,qr,d,mid+1,r,rc);
	pushup(p);
}
void change(int pos,int d,int l=1,int r=n,int p=1){
	if(l==r)return miv[p]=d,void();
	int mid=(l+r)>>1;
	if(pos<=mid)change(pos,d,l,mid,lc);
	else change(pos,d,mid+1,r,rc);
	pushup(p);
}
pair<int,int>query(int ql,int qr,int l=1,int r=n,int p=1){
	if(ql>qr)return mkp(inf,inf);
	if(ql<=l&&r<=qr)return mkp(miv[p],id[p]);
	int mid=(l+r)>>1;pair<int,int>res=mkp(inf,inf);
	if(ql<=mid)ckmin(res,query(ql,qr,l,mid,lc));
	if(mid<qr)ckmin(res,query(ql,qr,mid+1,r,rc));
	return res;
}
#undef lc
#undef rc
}

namespace sg2{
#define lc (p<<1)
#define rc (p<<1|1)
int sv[T],sl[T],sr[T];
void pushup(int p){
	if(sl[lc])sl[p]=sl[lc];
	else sl[p]=sl[rc];
	if(sr[rc])sr[p]=sr[rc];
	else sr[p]=sr[lc];
	sv[p]=max(sv[lc],sv[rc]);
	if(sl[rc]&&sr[lc])ckmax(sv[p],sl[rc]-sr[lc]);
}
void change(int pos,int k,int l=1,int r=n,int p=1){
	if(l==r){
		sl[p]=sr[p]=k?l:0;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)change(pos,k,l,mid,lc);
	else change(pos,k,mid+1,r,rc);
	pushup(p);
}
int query(int l=1,int r=n,int p=1){
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(!sl[rc])return query(l,mid,lc);
	if(!sl[lc])return query(mid+1,r,rc);
	if(sv[rc]<len&&sl[rc]-sr[lc]<len)return query(l,mid,lc);
	return query(mid+1,r,rc);
}

#undef lc
#undef rc
}

int dis(int x,int y){
	return x<=y?y-x:y+n-x;
}
int compare_plants(int a,int b){
	++a,++b;
	int flg=1;
	if(tpn[a]>tpn[b])flg=-1,swap(a,b);
	LL dst=0;int u=a;
	for(int i=19;i>=0;--i)
		if(L[i][u]&&tpn[L[i][u]]<=tpn[b])dst+=dl[i][u],u=L[i][u];
	if(dst>=dis(b,a))return flg;
	dst=0,u=a;
	for(int i=19;i>=0;--i)
		if(R[i][u]&&tpn[R[i][u]]<=tpn[b])dst+=dr[i][u],u=R[i][u];
	if(dst>=dis(a,b))return flg;
	return 0;
}
inline bool cmp(const int&a,const int&b){
	return tpn[a]>tpn[b];
}
void init(int k,std::vector<int>r){
	len=k,n=r.size(),tpo=0;
	for(int i=0;i<n;++i)a[i+1]=r[i];
	sg1::build(1,n,1,a);
	for(int i=1;i<=n;++i)if(!a[i])sg2::change(i,1);
	for(int i=1;i<=n;++i){
		int x=sg1::id[1];
		if(x-k+1<1){
			pair<int,int>tmp=sg1::query(n+x-k+1,n);
			if(!tmp.fi)x=sg2::query();
		}
		tpn[x]=++tpo;
		sg1::change(x,inf),sg2::change(x,0);
		v0.clear();
		sg1::update(max(1,x-k+1),x,-1);
		if(x-k+1<1)sg1::update(n+x-k+1,n,-1);
		for(int j:v0)sg2::change(j,1);
	}
	for(int i=1;i<=n;++i)a[i]=inf;
	sg1::build(1,n,1,a);
	for(int i=1;i<=n;++i)a[i]=i;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i){
		int x=a[i],le=0,ri=0;
		pair<int,int>tl=sg1::query(max(1,x-k+1),x);
		if(tl.fi<inf)le=tl.se;
		if(x-k+1<1){
			pair<int,int>ttl=sg1::query(n+x-k+1,n);
			if(tl.fi>ttl.fi)le=ttl.se;
		}
		pair<int,int>tr=sg1::query(x,min(x+k-1,n));
		if(tr.fi<inf)ri=tr.se;
		if(x+k-1>n){
			pair<int,int>ttr=sg1::query(1,x+k-1-n);
			if(tr.fi>ttr.fi)ri=ttr.se;
		}
		sg1::change(x,tpn[x]);
		L[0][x]=le,R[0][x]=ri;
		dl[0][x]=dis(le,x),dr[0][x]=dis(x,ri);
	}
	for(int i=1;i<=19;++i)
		for(int j=1;j<=n;++j)
			L[i][j]=L[i-1][L[i-1][j]],R[i][j]=R[i-1][R[i-1][j]],
			dl[i][j]=dl[i-1][j]+dl[i-1][L[i-1][j]],
			dr[i][j]=dr[i-1][j]+dr[i-1][R[i-1][j]];
}