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
const int sq=sqrt(N);
int n,m,a[N],size;
int bel[N],ans[N],cnt[N],jump[N];
struct QUE {
	int opt,l,r,x,id;
}q[N];
struct node {
	int l,r,x,id;
	node(){}
	node(int l_,int r_,int x_,int i_){
		l=l_,r=r_,x=x_,id=i_;
	}
};
vector<node>p[sq+5];
int pre[N],mx[N];
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
	C=B,C>>=N-x,C&=A;
	return C.any();
}
int Q3(int x) {
	for(int i=1;i*i<=x;++i) {
		if(x%i)continue;
		if(A[i]&&A[x/i])return 1;
	}
	return 0;
}
int Q4(int x) {
	for(int i=1;i*x<N;++i)
		if(A[i]&&A[i*x])return 1;
	return 0;
}
void solve() {
	for(int i=1;i<=sq;++i) {
		if(p[i].empty())continue;
		memset(pre,0,sizeof(pre));
		memset(mx,0,sizeof(mx));
		int t=0;
		for(int j=1;j<=n;++j) {
			pre[a[j]]=j;
			if(i*a[j]<N)t=max(t,pre[i*a[j]]);
			if(a[j]%i==0)t=max(t,pre[a[j]/i]);
			mx[j]=t;
		}
		for(node x:p[i])
			ans[x.id]=(x.l<=mx[x.r]);
	}
}
signed main() {
	n=rd(),m=rd(),size=sqrt(n);
	for(int i=1;i<=n;++i)a[i]=rd(),bel[i]=(i-1)/size+1;
	for(int i=1;i<=m;++i) {
		int opt=rd(),l=rd(),r=rd(),x=rd();
		if(opt==4&&x<=sq){jump[i]=1;p[x].push_back(node(l,r,x,i));}
		q[i].opt=opt,q[i].l=l,q[i].r=r,q[i].x=x,q[i].id=i;
	}
	solve();
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;++i) {
		if(jump[q[i].id])continue;
		while(l<q[i].l)pop(l++);
		while(l>q[i].l)add(--l);
		while(r<q[i].r)add(++r);
		while(r>q[i].r)pop(r--);
		if(q[i].opt==1)ans[q[i].id]=Q1(q[i].x);
		else if(q[i].opt==2)ans[q[i].id]=Q2(q[i].x);
		else if(q[i].opt==3)ans[q[i].id]=Q3(q[i].x);
		else ans[q[i].id]=Q4(q[i].x);
	}
	for(int i=1;i<=m;++i)puts(ans[i]?"yuno":"yumi");
	return 0;
}