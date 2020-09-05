#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
#define N 200009
int n,ans,LX,LY,lshx[N],lshy[N],tr[N],cnt[N];
struct node {
    int x,y;
}a[N];
inline bool cmp(const node&a,const node&b) {
    return a.y!=b.y?a.y>b.y:a.x>b.x;
}
void add(int x,int d) {
    for(int i=x;i<=n;i+=i&-i)tr[i]+=d;
}
int ask(int x) {
    int res=0;
    for(int i=x;i>0;i-=i&-i)res+=tr[i];
    return res;
}
int ask(int l,int r){
    return ask(r)-ask(l-1);
}
signed main() {
    n=rd();
    for(int i=1;i<=n;++i)a[i].x=lshx[++LX]=rd(),a[i].y=lshy[++LY]=rd();
    sort(lshx+1,lshx+LX+1),sort(lshy+1,lshy+LY+1);
    LX=unique(lshx+1,lshx+LX+1)-lshx-1,LY=unique(lshy+1,lshy+LY+1)-lshy-1;
    for(int i=1;i<=n;++i)
        a[i].x=lower_bound(lshx+1,lshx+LX+1,a[i].x)-lshx,a[i].y=lower_bound(lshy+1,lshy+LY+1,a[i].y)-lshy;
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;++i) {
        if(!cnt[a[i].x])cnt[a[i].x]=1,add(a[i].x,1);
        ans+=ask(a[i].y==a[i+1].y?a[i+1].x+1:1,a[i].x)*ask(a[i].x,n);
    }
    printf("%lld\n",ans);
    return 0;
}