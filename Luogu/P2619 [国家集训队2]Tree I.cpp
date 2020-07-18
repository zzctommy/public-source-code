#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=50010;
const int M=100010;
struct node {
    int u,v,d,col;
}e[M];
bool cmp(const node &a,const node &b) {
    return a.d!=b.d?a.d<b.d:a.col<b.col;
}
int n,m,need,ans;
int sumval;
int fa[N];
int find(int x) {return x==fa[x]?x:fa[x]=find(fa[x]);}
int check(int x) {
    for(int i=1;i<=n;++i)fa[i]=i;
    for(int i=1;i<=m;++i)if(!e[i].col)e[i].d+=x;
    sort(e+1,e+m+1,cmp);
    int res=0;sumval=0;
    for(int i=1;i<=m;++i) {
        int fx=find(e[i].u),fy=find(e[i].v);
        if(fx!=fy)sumval+=e[i].d,res+=(!e[i].col),fa[fx]=fy;
    }
    for(int i=1;i<=m;++i)if(!e[i].col)e[i].d-=x;
    return res;
}
signed main() {
    n=rd(),m=rd(),need=rd();
    for(int i=1; i<=m; ++i)
        e[i].u=rd()+1,e[i].v=rd()+1,e[i].d=rd(),e[i].col=rd();
    int l=-100,r=100;
    while(l<=r) {
        int mid=(l+r)>>1,k=check(mid);
        if(k>=need)ans=sumval-need*mid,l=mid+1;
        else r=mid-1;
    }
    printf("%d\n",ans);
    return 0;
}