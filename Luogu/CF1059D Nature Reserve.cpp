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
#define int long long
inline int rd() {
    int a=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))a=a*10+(ch^48),ch=getchar();
    return a*f;
}
#define N 100009
struct node {
	db l,r;
	node(){}
	node(db l_,db r_){l=l_,r=r_;}
	node operator + (const node&t){return node(max(l,t.l),min(r,t.r));}
};
const db inf=1e15;
struct point {
	db x,y;
}a[N];
int n;
db ans=-1;
bool check(db k) {
	node res=node(-inf,inf);
	for(int i=1;i<=n;++i) {
		db delta=8*a[i].y*k-4*a[i].y*a[i].y;
		if(delta<0)return 0;
		node now=node(2*a[i].x-sqrt(delta),2*a[i].x+sqrt(delta));
		res=res+now;
	}
	return res.l-1e-10<res.r;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	bool f1=0,f2=0;
	for(int i=1;i<=n;++i) {
		cin>>a[i].x>>a[i].y;
		f1|=a[i].y>0,f2|=a[i].y<0;
		if(f1&&f2)return puts("-1"),0;
		a[i].y=fabs(a[i].y);
	}
	db l=-inf,r=inf;
	for(int i=1;i<=114;++i) {
		db mid=(l+r)/2;
		if(check(mid))ans=mid,r=mid;
		else l=mid;
	}
	if(fabs(ans+1)<1e-10)puts("-1");
	else printf("%.10lf\n",ans);
	return 0;
}