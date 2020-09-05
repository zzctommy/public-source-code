#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100010;
int n,m,k,a[N],bin[1<<20],size,bel[N];
LL ans[N],cur;
struct QUE {
	int id,l,r;
}q[N];
bool cmp(const QUE &a,const QUE &b) {
	return bel[a.l]!=bel[b.l]?a.l<b.l:bel[a.l]&1?a.r<b.r:a.r>b.r;
}
void pop(int x) {--bin[a[x]],cur-=bin[a[x]^k];}
void add(int x) {cur+=bin[a[x]^k],++bin[a[x]];}
signed main() {
	n=rd(),m=rd(),k=rd(),size=sqrt(n);
	for(rint i=1;i<=n;++i)a[i]=rd(),a[i]^=a[i-1],bel[i]=(i-1)/size+1;
	for(rint i=1;i<=m;++i)q[i].l=rd()-1,q[i].r=rd(),q[i].id=i;
	sort(q+1,q+m+1,cmp);
	for(rint i=1,l=1,r=0;i<=m;++i) {
		while(l<q[i].l)pop(l++);
		while(l>q[i].l)add(--l);
		while(r<q[i].r)add(++r);
		while(r>q[i].r)pop(r--);
		ans[q[i].id]=cur;
	}
	for(rint i=1;i<=m;++i)printf("%lld\n",ans[i]);
	return 0;
}