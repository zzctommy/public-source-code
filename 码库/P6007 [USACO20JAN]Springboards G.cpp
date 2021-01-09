#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100009;
int w,n,o,dp[N],dis[N];
struct node {
	int opt,x,y,id;//opt=1:modify;opt=0:query
}p[N<<1],q[N<<1];
inline bool cmpx(const node&a,const node&b) {
	if(a.x==b.x&&a.y==b.y)return a.opt>b.opt;
	return a.x!=b.x?a.x<b.x:a.y<b.y;
}
inline bool cmpy(const node&a,const node&b) {
	if(a.x==b.x&&a.y==b.y)return a.opt>b.opt;
	return a.y!=b.y?a.y<b.y:a.x<b.x;
}
void cdq(int l,int r) {
	if(l==r)return;
	int mid=(l+r)>>1;
	cdq(l,mid),sort(p+mid+1,p+r+1,cmpy);
	for(int i=mid+1,j=l,mx=0;i<=r;++i) {
		if(p[i].opt)continue;
		for(;j<=mid&&p[j].y<=p[i].y;++j)
			if(p[j].opt)mx=max(mx,dp[p[j].id]);
		dp[p[i].id]=max(dp[p[i].id],mx+dis[p[i].id]);
	}
	sort(p+mid+1,p+r+1,cmpx),cdq(mid+1,r);
	sort(p+l,p+r+1,cmpy);
}
signed main() {
	w=rd(),n=rd();
	for(int i=1,sx,sy,tx,ty;i<=n;++i)
		sx=rd(),sy=rd(),tx=rd(),ty=rd(),
		dis[i]=tx-sx+ty-sy,
		++o,p[o].id=i,p[o].opt=0,p[o].x=sx,p[o].y=sy,
		++o,p[o].id=i,p[o].opt=1,p[o].x=tx,p[o].y=ty;
	++o,p[o].id=0,p[o].opt=1,p[o].x=0,p[o].y=0;
	++o,p[o].id=n+1,p[o].opt=0,p[o].x=w,p[o].y=w;
	sort(p+1,p+o+1,cmpx);
	cdq(1,o);
	printf("%d\n",w*2-dp[n+1]);
	return 0;
}
