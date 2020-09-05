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
const int N=100009;
const int zky=1000000007;
const int inf=1e12;
int n,x,y,cnt,st[N],top,ans,l[N],r[N];
struct node {
	int x,id,o;
}a[N<<1];
inline bool cmp(const node&a,const node&b) {
	return a.x!=b.x?a.x<b.x:a.o<b.o;
}
signed main() {
	n=rd(),x=rd(),y=rd();
	for(int i=1;i<=n;++i)
		++cnt,a[cnt].x=l[i]=rd(),a[cnt].id=i,a[cnt].o=0,
		++cnt,a[cnt].x=r[i]=rd(),a[cnt].id=i,a[cnt].o=1;
	sort(a+1,a+cnt+1,cmp);
	for(int i=1;i<=cnt;++i) {
		if(a[i].o)st[++top]=a[i].x;
		else {
			int t=r[a[i].id];
			if(!top)ans=(ans+x+y*(t-a[i].x)%zky)%zky;
			else {
				int tx=x+y*(t-a[i].x),ty=y*(t-st[top]);
				if(tx<ty)ans=(ans+tx)%zky;
				else ans=(ans+ty)%zky,--top;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}