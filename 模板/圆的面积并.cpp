#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return x*f;
}
const int N=1010;
struct cir {
    double r,x,y;
}o[N];
struct line {
    double l,r;
}l[N];
double L,R;
int n;
double p2(double x) {return x*x;}
bool cmp(const line &a,const line &b) {
    return a.l<b.l;
}
double f(double x) {
    int tot=0;double lst=-1e10,res=0;
    for(rint i=1;i<=n;++i)
        if(fabs(x-o[i].x)-o[i].r<0) {
            double len=sqrt(p2(o[i].r)-p2(o[i].x-x));
            ++tot,l[tot].l=o[i].y-len,l[tot].r=o[i].y+len;
        }
    sort(l+1,l+tot+1,cmp);
    for(rint i=1;i<=tot;++i)
        if(lst<l[i].l)res+=l[i].r-l[i].l,lst=l[i].r;
        else if(lst<l[i].r)res+=l[i].r-lst,lst=l[i].r;
    return res;
}
double simpson(double l,double r) {
    return (f(l)+4*f((l+r)/2)+f(r))*(r-l)/6;
}
double work(double l,double r,double eps,double val) {
    double mid=(l+r)/2,lv=simpson(l,mid),rv=simpson(mid,r);
    if(fabs(lv+rv-val)<15*eps)return lv+rv+(lv+rv-val)/15;
    return work(l,mid,eps/2,lv)+work(mid,r,eps/2,rv);
}
double ask(double l,double r,double eps) {
    return work(l,r,eps,simpson(l,r));
}
signed main() {
    n=rd();double eps=1e-4;
    for(rint i=1;i<=n;++i)
        scanf("%lf%lf%lf",&o[i].x,&o[i].y,&o[i].r),
        L=min(o[i].x-o[i].r,L),R=max(o[i].x+o[i].r,R);
    printf("%.3lf\n",ask(L,R,eps));
    return 0;
}
