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
const int M=500010;
struct node {
    int u,v,d;
}a[M],b[M],c[M];
int n,m,need,s;
int cnta,cntb,cntc;
LL sumval,ans;
int fa[N];
int find(int x) {return x==fa[x]?x:fa[x]=find(fa[x]);}
int cns(const node &a) {return a.u==s||a.v==s;}
bool cmp(const node &a,const node &b) {return a.d<b.d;}
void msort(node *a,node *b) {
    int i=1,j=1;cntc=0;
    while(i<=cnta&&j<=cntb) {
        if(a[i].d<=b[j].d)c[++cntc]=a[i++];
        else c[++cntc]=b[j++];
    }
    while(i<=cnta)c[++cntc]=a[i++];
    while(j<=cntb)c[++cntc]=b[j++];
}
int check(int x) {
    for(int i=1;i<=n;++i)fa[i]=i;
    for(int i=1;i<=cnta;++i)a[i].d+=x;
    msort(a,b);
    int res=0,num=0;sumval=0;
    for(int i=1;i<=m&&num<n-1;++i) {
        int fx=find(c[i].u),fy=find(c[i].v);
        if(fx!=fy)sumval+=c[i].d,res+=cns(c[i]),fa[fx]=fy,++num;
    }
    for(int i=1;i<=cnta;++i)a[i].d-=x;
    return res;
}
signed main() {
    n=rd(),m=rd(),s=rd(),need=rd();
    int l=0,r=0,res;
    for(int i=1;i<=m;++i) {
        int x=rd(),y=rd(),z=rd();
        if(x==s||y==s)++cnta,a[cnta].u=x,a[cnta].v=y,a[cnta].d=z;
        else ++cntb,b[cntb].u=x,b[cntb].v=y,b[cntb].d=z;
        r=max(r,z);
    }
    l=-r;
    sort(a+1,a+cnta+1,cmp);
    sort(b+1,b+cntb+1,cmp);
    if(check(l)<need)return puts("Impossible"),0;
    if(check(r)>need)return puts("Impossible"),0;
    while(l<=r) {
        int mid=(l+r)>>1,k=check(mid);
        if(k>=need)res=mid,l=mid+1;
        else r=mid-1;
    }
    check(res);
    printf("%lld\n",sumval-1ll*res*need);
    return 0;
}
