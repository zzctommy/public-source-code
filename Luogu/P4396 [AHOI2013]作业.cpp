#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100009;
int n,m,pre[N],a[N],size,bel[N],ans[N][2],bin[N];
struct BIT {
	int tr[N];
	void add(int x,int d){
		if(!x)return;
		for(int i=x;i<N;i+=i&-i)tr[i]+=d;
	}
	int ask(int x) {
		int res=0;
		for(int i=x;i>0;i-=i&-i)res+=tr[i];
		return res;
	}
	int ask(int l,int r){return ask(r)-ask(l-1);}
}t[2];
struct ASK {
	int l,r,a,b,id;
}q[N];
inline bool cmp(const ASK&a,const ASK&b) {
	return bel[a.l]!=bel[b.l]?a.l<b.l:bel[a.l]&1?a.r<b.r:a.r>b.r;
}
void add(int x) {
	t[0].add(a[x],1),++bin[a[x]];
	if(bin[a[x]]==1)t[1].add(a[x],1);
}
void pop(int x) {
	t[0].add(a[x],-1),--bin[a[x]];
	if(bin[a[x]]==0)t[1].add(a[x],-1);
}
signed main() {
	n=rd(),m=rd(),size=sqrt(n);
	for(int i=1;i<=n;++i)a[i]=rd(),bel[i]=(i-1)/size+1;
	for(int i=1;i<=m;++i)q[i].id=i,q[i].l=rd(),q[i].r=rd(),q[i].a=rd(),q[i].b=rd();
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;++i) {
		while(l<q[i].l)pop(l++);
		while(l>q[i].l)add(--l);
		while(r<q[i].r)add(++r);
		while(r>q[i].r)pop(r--);
		ans[q[i].id][0]=t[0].ask(q[i].a,q[i].b);
		ans[q[i].id][1]=t[1].ask(q[i].a,q[i].b);
	}
	for(int i=1;i<=m;++i)printf("%d %d\n",ans[i][0],ans[i][1]);
	return 0;
}