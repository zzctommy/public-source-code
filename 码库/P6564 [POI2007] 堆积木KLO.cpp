#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
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
const int N=100005;
int n,tr[N];
void upd(int x,int d){for(int i=x;i<=n;i+=i&-i)tr[i]=max(tr[i],d);}
int ask(int x){int res=0;for(int i=x;i>0;i-=i&-i)res=max(res,tr[i]);return res;}
struct node {
	int x,y,val;
	inline bool operator < (const node&rhs)const{return x!=rhs.x?x<rhs.x:y<rhs.y;}
}a[N];
signed main() {
	n=rd();
	for(int i=1;i<=n;++i)a[i].x=i-(a[i].val=rd()),a[i].y=i;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i){
		if(a[i].x<0) continue;
		upd(a[i].val,ask(a[i].val-1)+1);
	}
	printf("%d\n",ask(n));
	return 0;
}
