#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100010;
int n,m,a[N],size;
int bel[N],ans[N],cnt[N];
struct QUE {
	int opt,l,r,x,id;
}q[N];
inline bool cmp(const QUE &a,const QUE &b) {
	return bel[a.l]!=bel[b.l]?a.l<b.l:bel[a.l]&1?a.r<b.r:a.r>b.r;
}
bitset<N>A,B,C;
void add(int x) {
	++cnt[a[x]];
	if(cnt[a[x]])A[a[x]]=1,B[N-a[x]]=1;
	else A[a[x]]=0,B[N-a[x]]=0;
}
void pop(int x) {
	--cnt[a[x]];
	if(cnt[a[x]])A[a[x]]=1,B[N-a[x]]=1;
	else A[a[x]]=0,B[N-a[x]]=0;
}
int Q1(int x) {
	C=A,C<<=x,C&=A;
	return C.any();
}
int Q2(int x) {
	C=B,C>>=(N-x),C&=A;
	return C.any();
}
int Q3(int x) {
	for(int i=1;i*i<=x;++i) {
		if(x%i)continue;
		if(A[i]&&A[x/i])return 1;
	}
	return 0;
}
signed main() {
	n=rd(),m=rd(),size=sqrt(n);
	for(int i=1;i<=n;++i)a[i]=rd(),bel[i]=(i-1)/size+1;
	for(int i=1;i<=m;++i)q[i].opt=rd(),q[i].l=rd(),q[i].r=rd(),q[i].x=rd(),q[i].id=i;
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;++i) {
		while(l<q[i].l)pop(l++);
		while(l>q[i].l)add(--l);
		while(r<q[i].r)add(++r);
		while(r>q[i].r)pop(r--);
		if(q[i].opt==1)ans[q[i].id]=Q1(q[i].x);
		else if(q[i].opt==2)ans[q[i].id]=Q2(q[i].x);
		else if(q[i].opt==3)ans[q[i].id]=Q3(q[i].x);
	}
	for(int i=1;i<=m;++i)puts(ans[i]?"hana":"bi");
	return 0;
}