#pragma GCC optimize(2)
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
const int N=500010;
int n,a[N],m,ans[N];
int size,bel[N],C;
int st[N],top,cnt[N],del[N];
struct QUE {
	int id,l,r;
}que[N];
bool cmp(const QUE &a,const QUE &b) {
	return bel[a.l]!=bel[b.l]?bel[a.l]<bel[b.l]:bel[a.l]&1?a.r<b.r:a.r>b.r;
}
void add(int x) {
	if(cnt[x]==1)++del[x];
	++cnt[x];
	if(cnt[x]==1) {
		if(del[x])--del[x];
		else st[++top]=x;
	}
}
void pop(int x) {
	if(cnt[x]==1)++del[x];
	--cnt[x];
	if(cnt[x]==1) {
		if(del[x])--del[x];
		else st[++top]=x;
	}
}
signed main() {
	n=rd(),size=sqrt(n);
	for(rint i=1;i<=n;++i)
		a[i]=rd(),C=max(a[i],C),bel[i]=(i-1)/size+1;
	m=rd();
	for(rint i=1;i<=m;++i)
		que[i].id=i,que[i].l=rd(),que[i].r=rd();
	sort(que+1,que+m+1,cmp);
	for(rint i=1,l=1,r=0;i<=m;++i) {
		while(l<que[i].l)pop(a[l++]);
		while(l>que[i].l)add(a[--l]);
		while(r<que[i].r)add(a[++r]);
		while(r>que[i].r)pop(a[r--]);
		while(del[st[top]]&&top)--del[st[top--]];
		ans[que[i].id]=st[top];
	}
	for(rint i=1;i<=m;++i)printf("%d\n",ans[i]);
	return 0;
}