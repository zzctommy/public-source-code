#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=1145140;
struct QUE {
	int t,x,y,z;
	inline bool operator < (const QUE&rhs){
		return x<rhs.x;
	}
}a[N],p[N],fyyAKIOI[N];
int n,m,k,X,Y,tr[N],ans[N];
void add(int x,int d) {
	for(int i=x;i<=Y;i+=i&-i)tr[i]=max(tr[i],d);
}
int ask(int x) {
	int res=0;
	for(int i=x;i>0;i-=i&-i)res=max(res,tr[i]);
	return res;
}
void clear(int x) {
	for(int i=x;i<=Y;i+=i&-i)tr[i]=0;
}
void init() {
	k=0;int tx=0,ty=0;
	for(int i=1;i<=n;++i)
		if(!p[i].t)tx=max(tx,p[i].x),ty=max(ty,p[i].y);
	for(int i=1;i<=n;++i)
		if(p[i].x<=tx&&p[i].y<=ty)fyyAKIOI[++k]=p[i];
	for(int i=1;i<=k;++i)p[i]=fyyAKIOI[i];
}
void cdq(int l,int r) {
	if(l==r)return;
	int mid=(l+r)>>1;
	cdq(l,mid),cdq(mid+1,r);
	for(int i=mid+1,j=l;i<=r;++i) {
		if(p[i].t)continue;
		for(;j<=mid&&p[j].x<=p[i].x;++j)
			if(p[j].t)add(p[j].y,p[j].x+p[j].y);
		int tmp=ask(p[i].y);
		if(tmp)ans[p[i].z]=min(ans[p[i].z],p[i].x+p[i].y-tmp);
	}
	for(int i=l;i<=mid;++i)if(p[i].t)clear(p[i].y);
	merge(p+l,p+mid+1,p+mid+1,p+r+1,fyyAKIOI+l);
	for(int i=l;i<=r;++i)p[i]=fyyAKIOI[i];
}
signed main() {
	n=rd(),m=rd();
	for(int i=1;i<=n;++i) {
		a[i].t=1,a[i].z=i,a[i].x=rd()+1,a[i].y=rd()+1;
		X=max(X,a[i].x),Y=max(Y,a[i].y);
	}
	for(int i=1;i<=m;++i) {
		++n,a[n].t=rd()&1,a[n].z=n,a[n].x=rd()+1,a[n].y=rd()+1;
		X=max(X,a[n].x),Y=max(Y,a[n].y);
	}
	memset(ans,0x3f,sizeof(ans));
	for(int i=1;i<=n;++i)p[i]=a[i];
	init(),cdq(1,k);
	for(int i=1;i<=n;++i)p[i]=a[i],p[i].x=X-a[i].x+1;
	init(),cdq(1,k);
	for(int i=1;i<=n;++i)p[i]=a[i],p[i].y=Y-a[i].y+1;
	init(),cdq(1,k);
	for(int i=1;i<=n;++i)p[i]=a[i],p[i].x=X-a[i].x+1,p[i].y=Y-a[i].y+1;
	init(),cdq(1,k);
	for(int i=1;i<=n;++i)if(!a[i].t)printf("%d\n",ans[i]);
	return 0;
}
