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
#define N 1000009
int n,m,a[N];
char s[N];
int tag[N<<2],val[N<<2][4];
#define lc (p<<1)
#define rc (p<<1|1)
void pushup(int p) {
	val[p][0]=val[lc][0]+val[rc][0];//0
	val[p][1]=val[lc][1]+val[rc][1];//1
	val[p][2]=max(max(val[lc][0],val[lc][2])+val[rc][1],max(val[rc][1],val[rc][2])+val[lc][0]);//0->1
	val[p][3]=max(max(val[lc][1],val[lc][3])+val[rc][0],max(val[rc][0],val[rc][3])+val[lc][1]);//1->0
}
void build(int l,int r,int p) {
	if(l==r)return val[p][a[l]]=val[p][2]=val[p][3]=1,void();
	int mid=(l+r)>>1;build(l,mid,lc),build(mid+1,r,rc);
	pushup(p);
}
void addtag(int p) {
	tag[p]^=1,swap(val[p][0],val[p][1]),swap(val[p][2],val[p][3]);
}
void pushdown(int p,int l,int r) {
	if(tag[p])addtag(lc),addtag(rc),tag[p]^=1;
}
void update(int ql,int qr,int l,int r,int p) {
	if(ql<=l&&r<=qr)return addtag(p),void();
	pushdown(p,l,r);
	int mid=(l+r)>>1;
	if(ql<=mid)update(ql,qr,l,mid,lc);
	if(qr>mid)update(ql,qr,mid+1,r,rc);
	pushup(p);
}
signed main() {
	n=rd(),m=rd(),scanf("%s",s+1);
	for(int i=1;i<=n;++i)a[i]=s[i]=='7';
	build(1,n,1);
	while(m--) {
		scanf("%s",s);
		int opt=s[0]=='s',x,y;
		if(opt)x=rd(),y=rd(),update(x,y,1,n,1);
		else printf("%d\n",val[1][2]);
	}
	return 0;
}