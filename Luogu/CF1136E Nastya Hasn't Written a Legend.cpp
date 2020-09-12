#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
#define int long long
#define N 100009
const int inf=1e18;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
inline int rdc() {
	char ch=getchar();
	while(ch!='+'&&ch!='s')ch=getchar();
	return ch=='s';
}
int a[N],k[N],s[N],v[N],n,ss[N];
int val[N<<2],tag[N<<2],miv[N<<2];
#define lc (p<<1)
#define rc (p<<1|1)
void pushup(int p) {
	val[p]=val[lc]+val[rc],miv[p]=std::min(miv[lc],miv[rc]);
}
void build(int l,int r,int p) {
	tag[p]=inf;
	if(l==r)return val[p]=miv[p]=v[l],void();
	int mid=(l+r)>>1;
	build(l,mid,lc),build(mid+1,r,rc);
	pushup(p);
}
void pushdown(int p,int l,int r) {
	if(tag[p]==inf)return;
	int mid=(l+r)>>1;
	tag[lc]=tag[rc]=tag[p];
	miv[lc]=miv[rc]=tag[p];
	val[lc]=tag[p]*(mid-l+1);
	val[rc]=tag[p]*(r-mid);
	tag[p]=inf;
}
int query(int ql,int qr,int l,int r,int p) {
	if(ql<=l&&r<=qr)return val[p];
	pushdown(p,l,r);
	int mid=(l+r)>>1,res=0;
	if(ql<=mid)res+=query(ql,qr,l,mid,lc);
	if(mid<qr)res+=query(ql,qr,mid+1,r,rc);
	return res;
}
void update(int ql,int qr,int l,int r,int p,int k) {
	if(ql<=l&&r<=qr) {
		tag[p]=miv[p]=k,val[p]=k*(r-l+1);return;
	}
	pushdown(p,l,r);
	int mid=(l+r)>>1;
	if(ql<=mid)update(ql,qr,l,mid,lc,k);
	if(mid<qr)update(ql,qr,mid+1,r,rc,k);
	pushup(p);
}
int ask(int v,int l,int r,int p) {
	if(l==r)return l;
	pushdown(p,l,r);
	int mid=(l+r)>>1;
	if(miv[rc]<=v)return ask(v,mid+1,r,rc);
	else return ask(v,l,mid,lc);
}
signed main() {
	n=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	for(int i=2;i<=n;++i)k[i]=rd(),s[i]=s[i-1]+k[i],ss[i]=ss[i-1]+s[i];
	for(int i=1;i<=n;++i)v[i]=a[i]-s[i];
	build(1,n,1);
	for(int q=rd();q;--q) {
		int opt=rdc(),x=rd(),y=rd();
		if(opt)printf("%lld\n",query(x,y,1,n,1)+ss[y]-ss[x-1]);
		else {
			int now=query(x,x,1,n,1);
			update(x,ask(now+y,1,n,1),1,n,1,now+y);
		}
	}
	return 0;
}
//zky txdy!