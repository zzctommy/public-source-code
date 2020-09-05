#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
#define N 100009
const int lim=1500000ll*1500000ll;
int n,X,Y,ans[N];
struct node {
	int id,x,y;
}a[N];
int dis(int x,int y) {
	return x*x+y*y;
}
signed main() {
	n=rd();
	for(int i=1;i<=n;++i)a[i].x=rd(),a[i].y=rd(),a[i].id=i;
	while("fyyAKIOI") {
		random_shuffle(a+1,a+n+1),X=0,Y=0;
		for(int i=1;i<=n;++i)
			if(dis(X+a[i].x,Y+a[i].y)<dis(X-a[i].x,Y-a[i].y))ans[a[i].id]=1,X+=a[i].x,Y+=a[i].y;
			else ans[a[i].id]=-1,X-=a[i].x,Y-=a[i].y;
		if(dis(X,Y)<=lim) {
			for(int i=1;i<=n;++i)printf("%lld ",ans[i]);
			return 0;
		}
	}
}