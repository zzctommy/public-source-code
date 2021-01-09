#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(a) push_back(a)
#define mkp(a,y) make_pair(a,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int a=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))a=a*10+(ch^48),ch=getchar();
    return a*f;
}
#define N 100009
int n,m,a[N];
LL val[N<<2],tag[N<<2];
#define lc (p<<1)
#define rc (p<<1|1)
void pushup(int p) {val[p]=val[lc]+val[rc];}
void build(int l,int r,int p) {
	if(l==r)return val[p]=a[l],void();
	int mid=(l+r)>>1;
	build(l,mid,lc),build(mid+1,r,rc);
	pushup(p);
}
void pushdown(int p,int l,int r) {
	if(tag[p]) {
		int mid=(l+r)>>1;
		tag[lc]+=tag[p],val[lc]+=tag[p]*(mid-l+1);
		tag[rc]+=tag[p],val[rc]+=tag[p]*(r-mid);
		tag[p]=0;
	}
}
void update(int ql,int qr,int l,int r,int k,int p) {
	if(ql<=l&&r<=qr)return tag[p]+=k,val[p]+=k*(r-l+1),void();
	pushdown(p,l,r);
	int mid=(l+r)>>1;
	if(ql<=mid)update(ql,qr,l,mid,k,lc);
	if(qr>mid)update(ql,qr,mid+1,r,k,rc);
	pushup(p);
}
LL query(int ql,int qr,int l,int r,int p) {
	if(ql<=l&&r<=qr)return val[p];
	int mid=(l+r)>>1;LL res=0;
	pushdown(p,l,r);
	if(ql<=mid)res+=query(ql,qr,l,mid,lc);
	if(qr>mid)res+=query(ql,qr,mid+1,r,rc);
	return res;
}
signed main() {
	n=rd(),m=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	build(1,n,1);
	while(m--) {
		int opt=rd(),x=rd(),y=rd(),z;
		if(opt==1)z=rd(),update(x,y,1,n,z,1);
		else if(opt==2)printf("%lld\n",query(x,y,1,n,1));
	}
	return 0;
}