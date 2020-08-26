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
const int N=100009;
int n,m,o,a[N],pre[N],suf[N],numq,tr[N];
LL ans[N];
set<int>s[N];
struct node {
	int opt,x,y,v,id;
	inline bool operator < (const node&rhs)const{return x<rhs.x;}
}p[N*7],q[N*7];
#define IT set<int>::iterator
int suf_(int v,int x){
	return *s[v].upper_bound(x);
}
int pre_(int v,int x){
	IT it=s[v].lower_bound(x);--it;return *it;
}
void link(int x,int y) {
	++o,p[o].opt=0,p[o].x=x,p[o].y=pre[x],p[o].v=pre[x]-x,p[o].id=0;
	pre[x]=y;
	++o,p[o].opt=0,p[o].x=x,p[o].y=pre[x],p[o].v=x-pre[x],p[o].id=0;
}
void add(int x,int d) {
	if(!x)return;
	for(int i=x;i<=n;i+=i&-i)tr[i]+=d;
}
int ask(int x) {
	int res=0;
	for(int i=x;i>0;i-=i&-i)res+=tr[i];
	return res;
}
void clear(int x) {
	if(!x)return;
	for(int i=x;i<=n;i+=i&-i)tr[i]=0;
}
void cdq(int l,int r) {
	if(l==r)return;
	int mid=(l+r)>>1;
	cdq(l,mid),cdq(mid+1,r);
	for(int i=mid+1,j=l;i<=r;++i) {
		if(!p[i].opt)continue;
		for(;j<=mid&&p[j].x<=p[i].x;++j)
			if(!p[j].opt)add(p[j].y,p[j].v);
		ans[p[i].id]+=ask(n)-ask(p[i].y-1);
	}
	for(int i=l;i<=mid;++i)if(!p[i].opt)clear(p[i].y);
	merge(p+l,p+mid+1,p+mid+1,p+r+1,q+l);
	for(int i=l;i<=r;++i)p[i]=q[i];
}
signed main() {
	n=rd(),m=rd();
	for(int i=1;i<=n;++i)a[i]=rd(),s[a[i]].insert(i);
	for(int i=1;i<=n;++i)s[i].insert(0),s[i].insert(n+1);
	for(int i=1;i<=n;++i)
		pre[i]=pre_(a[i],i),suf[i]=suf_(a[i],i),
		++o,p[o].opt=0,p[o].x=i,p[o].y=pre[i],p[o].v=i-pre[i],p[o].id=0;
	for(int i=1;i<=m;++i) {
		int opt=rd(),x=rd(),y=rd();
		if(opt==2)++o,++numq,p[o].opt=1,p[o].x=y,p[o].y=x,p[o].id=numq;
		else {
			if(y==a[x])continue;
			int P=pre_(y,x),S=suf_(y,x);
			s[y].insert(x),s[a[x]].erase(x),a[x]=y;
			if(suf[x]!=n+1)link(suf[x],pre[x]);
			if(pre[x])suf[pre[x]]=suf[x];
			if(S!=n+1)link(S,x);
			if(P)suf[P]=x;
			link(x,P);
			suf[x]=S;
		}
	}
	cdq(1,o);
	for(int i=1;i<=numq;++i)printf("%lld\n",ans[i]);
	return 0;
}
