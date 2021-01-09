#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100010;
const int LOG=20;
int n,a[N];
struct SegmentTree {
	#define lc (p<<1)
	#define rc (p<<1|1)
	int tag[N<<2],val[N<<2];
	void pushup(int p) {
		val[p]=val[lc]+val[rc];
	}
	void flip(int p,int l,int r) {
		val[p]=r-l+1-val[p],tag[p]^=1;
	}
	void pushdown(int p,int l,int r) {
		if(!tag[p])return;
		int mid=(l+r)>>1;
		flip(lc,l,mid),flip(rc,mid+1,r);
		tag[p]=0;
	}
	void update(int ql,int qr,int l,int r,int p) {
		if(ql<=l&&r<=qr)return void(flip(p,l,r));
		pushdown(p,l,r);
		int mid=(l+r)>>1;
		if(ql<=mid)update(ql,qr,l,mid,lc);
		if(qr>mid)update(ql,qr,mid+1,r,rc);
		pushup(p);
	}
	int query(int ql,int qr,int l,int r,int p) {
		if(ql<=l&&r<=qr)return val[p];
		pushdown(p,l,r);
		int mid=(l+r)>>1;LL res=0;
		if(ql<=mid)res+=query(ql,qr,l,mid,lc);
        if(qr>mid)res+=query(ql,qr,mid+1,r,rc);
        return res;
	}
}T[LOG];
signed main() {
	n=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	for(int i=0;i<LOG;++i)
		for(int j=1;j<=n;++j)
			if(a[j]>>i&1)T[i].update(j,j,1,n,1);
	for(int m=rd();m;--m) {
		int opt=rd(),l=rd(),r=rd();
		if(opt==1) {
			LL sum=0;
			for(int i=0;i<LOG;++i)sum+=(1ll<<i)*T[i].query(l,r,1,n,1);
			printf("%lld\n",sum);
		} else {
			int x=rd();
			for(int i=0;i<LOG;++i)if(x>>i&1)T[i].update(l,r,1,n,1);
		}
	}
	return 0;
}