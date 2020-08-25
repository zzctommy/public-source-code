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
const int N=200009;
const int M=2000009;
int n,w,ans[N],cnt,tr[M];
bool isquery[N];
struct ASK {
	int id,opt,c,x,y,val;
	inline bool operator < (const ASK&rhs)const{return x<rhs.x;}
}p[N],q[N];
void add(int x,int d) {
	if(!x)return;
	for(int i=x;i<=w;i+=i&-i)tr[i]+=d;
}
int ask(int x) {
	int res=0;
	for(int i=x;i>0;i-=i&-i)res+=tr[i];
	return res;
}
void clear(int x) {
	if(!x)return;
	for(int i=x;i<=w;i+=i&-i)tr[i]=0;
}
void cdq(int l,int r) {
	if(l==r)return;
	int mid=(l+r)>>1;
	cdq(l,mid),cdq(mid+1,r);
	for(int i=mid+1,j=l;i<=r;++i) {
		if(p[i].opt)continue;
		for(;j<=mid&&p[j].x<=p[i].x;++j)
			if(p[j].opt)add(p[j].y,p[j].val);
		ans[p[i].id]+=p[i].c*ask(p[i].y);
	}
	for(int i=l;i<=mid;++i)if(p[i].opt)clear(p[i].y);
	merge(p+l,p+mid+1,p+mid+1,p+r+1,q+l);
	for(int i=l;i<=r;++i)p[i]=q[i];
}
signed main() {
	rd(),w=rd();
	while("fyyAKIOI") {
		int opt=rd(),x,y,z,k;
		if(opt==3)break;
		opt&=1,++cnt,x=rd(),y=rd(),z=rd();
		if(opt)++n,p[n].opt=opt,p[n].x=x,p[n].y=y,p[n].id=cnt,p[n].val=z;
		else {
			isquery[cnt]=1,k=rd();
			++n,p[n].opt=opt,p[n].x=z,p[n].y=k,p[n].id=cnt,p[n].c=1;
			++n,p[n].opt=opt,p[n].x=x-1,p[n].y=y-1,p[n].id=cnt,p[n].c=1;
			++n,p[n].opt=opt,p[n].x=x-1,p[n].y=k,p[n].id=cnt,p[n].c=-1;
			++n,p[n].opt=opt,p[n].x=z,p[n].y=y-1,p[n].id=cnt,p[n].c=-1;
		}
	}
	cdq(1,n);
	for(int i=1;i<=cnt;++i)if(isquery[i])printf("%d\n",ans[i]);
	return 0;
}
