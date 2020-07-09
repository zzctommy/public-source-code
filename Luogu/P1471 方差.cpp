#include<bits/stdc++.h>
using namespace std;
#define rint register int
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
const int N=1000010;
double s1[N<<2],s2[N<<2],tag[N<<2],a[N];
int n,m;
#define lc (p<<1)
#define rc (p<<1|1)
void pushup(int p) {
	s1[p]=s1[lc]+s1[rc],s2[p]=s2[lc]+s2[rc];
}
void build(int l,int r,int p) {
	if(l==r) {
		s1[p]=a[l];
		s2[p]=a[l]*a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,lc),build(mid+1,r,rc);
	pushup(p);
}
void addtag(int p,int l,int r,double d) {
	s2[p]+=2*d*s1[p]+d*d*(r-l+1);
	s1[p]+=d*(r-l+1);
	tag[p]+=d;
}
void pushdown(int p,int l,int r) {
	int mid=(l+r)>>1;
	addtag(lc,l,mid,tag[p]);
	addtag(rc,mid+1,r,tag[p]);
	tag[p]=0;
}
void update(int ql,int qr,int l,int r,int p,double k) {
	if(ql<=l&&r<=qr) {
		addtag(p,l,r,k);return;
	}
	pushdown(p,l,r);
	int mid=(l+r)>>1;
	if(mid>=ql)update(ql,qr,l,mid,lc,k);
	if(mid<qr)update(ql,qr,mid+1,r,rc,k);
	pushup(p);
}
double query1(int ql,int qr,int l,int r,int p) {
	if(ql<=l&&r<=qr)return s1[p];
	pushdown(p,l,r);
	int mid=(l+r)>>1;double res=0;
	if(mid>=ql)res+=query1(ql,qr,l,mid,lc);
	if(mid<qr)res+=query1(ql,qr,mid+1,r,rc);
	return res;
}
double query2(int ql,int qr,int l,int r,int p) {
	if(ql<=l&&r<=qr)return s2[p];
	pushdown(p,l,r);
	int mid=(l+r)>>1;double res=0;
	if(mid>=ql)res+=query2(ql,qr,l,mid,lc);
	if(mid<qr)res+=query2(ql,qr,mid+1,r,rc);
	return res;
}
signed main() {
	n=rd(),m=rd();
	for(rint i=1;i<=n;++i)scanf("%lf",&a[i]);
	build(1,n,1);
	while(m--) {
		int opt=rd(),x=rd(),y=rd();double z;
		if(opt==1) scanf("%lf",&z),update(x,y,1,n,1,z);
		else if(opt==2)printf("%.4lf\n",query1(x,y,1,n,1)/(y-x+1));
		else {
			double sum=query1(x,y,1,n,1),ave=sum/(y-x+1);
			printf("%.4lf\n",(query2(x,y,1,n,1)-2*sum*ave+(y-x+1)*ave*ave)/(y-x+1));
		}
	}
	return 0;
}
