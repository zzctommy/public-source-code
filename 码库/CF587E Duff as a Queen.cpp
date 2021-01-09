#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<vector>
#include<iostream>
#include<cmath>
using std::cout;
using std::endl;
using std::vector;
using std::lower_bound;
using std::unique;
using std::sort;
using std::max;
using std::min;
inline int rd(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch))f=(ch=='-'?0:f),ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}

#define N 200009
#define T (N<<2)
#define A 30

//LinearBase
struct LinearBase {
	int d[A+1],cnt;
	LinearBase(){memset(d,0,sizeof(d)),cnt=0;}
	void insert(int x) {
		for(int i=A;~i;--i)
			if(x>>i&1) {
				if(d[i])x^=d[i];
				else return d[i]=x,++cnt,void();
			}
	}
	int query(int x) {
		return (1ll<<cnt);
	}
	void reset() {
		memset(d,0,sizeof(d)),cnt=0;
	}
};

LinearBase merge(const LinearBase&a,const LinearBase&b){
	LinearBase res=a;
	for(int i=A;~i;--i)if(b.d[i])res.insert(b.d[i]);
	return res;
}

//Data
int n,m,a[N];
int tr[N];
LinearBase lb[T];

//BIT
void add(int x,int d) {
	if(!x)return;
	for(int i=x;i<=n;i+=i&-i)tr[i]^=d;
}

int ask(int x) {
	int res=0;
	for(int i=x;i>0;i-=i&-i)res^=tr[i];
	return res;
}

//SegmentTree
#define lc (p<<1)
#define rc (p<<1|1)

void pushup(int p) {lb[p]=merge(lb[lc],lb[rc]);}

void build(int l,int r,int p) {
	if(l==r) {
		lb[p].insert(a[l]);
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,lc),build(mid+1,r,rc);
	pushup(p);
}

void change(int pos,int l,int r,int p,int v) {
	if(l==r) {
		lb[p].reset(),lb[p].insert(a[l]^=v);
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)change(pos,l,mid,lc,v);
	else change(pos,mid+1,r,rc,v);
	pushup(p);
}

LinearBase query(int ql,int qr,int l,int r,int p) {
	if(ql<=l&&r<=qr)return lb[p];
	int mid=(l+r)>>1;LinearBase res;
	if(ql<=mid)res=merge(res,query(ql,qr,l,mid,lc));
	if(mid<qr)res=merge(res,query(ql,qr,mid+1,r,rc));
	return res;
}

//Main
signed main() {
	n=rd(),m=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	for(int i=n;i>=1;--i)a[i]^=a[i-1],add(i,a[i]);
	build(1,n,1);
	while(m--) {
		int opt=rd(),l=rd(),r=rd(),v;
		if(opt&1) {
			v=rd();
			add(l,v),change(l,1,n,1,v);
			if(r<n)add(r+1,v),change(r+1,1,n,1,v);
		}else {
			LinearBase res;
			if(l<r)res=query(l+1,r,1,n,1);
			res.insert(ask(l));
			printf("%d\n",res.query(v));
		}
	}
	return 0;
}
