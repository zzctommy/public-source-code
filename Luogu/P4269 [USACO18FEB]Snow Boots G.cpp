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
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
#define N 100009
int n,m,f[N],ans[N];
struct node {
    int id,s,d;
}a[N];
inline bool cmp1(const node&a,const node&b) {
    return a.s<b.s;
}
struct snow {
    int id,f;
}b[N];
inline bool cmp2(const snow&a,const snow&b) {
    return a.f<b.f;
}
set<int>w;
multiset<int>s;
typedef set<int>::iterator IT;
void add(int x) {
    IT Pre=w.lower_bound(x),Suf=w.upper_bound(x);
    --Pre;
    int pre=*Pre,suf=*Suf;
    s.erase(s.lower_bound(suf-pre));
    s.insert(x-pre),s.insert(suf-x);
    w.insert(x);
}
signed main() {
    n=rd(),m=rd();
    if(n==1) {
        for(int i=1;i<=m;++i)puts("1");
        return 0;
    }
    for(int i=1;i<=n;++i)b[i].f=f[i]=rd(),b[i].id=i;
    for(int i=1;i<=m;++i)a[i].id=i,a[i].s=rd(),a[i].d=rd();
    sort(a+1,a+m+1,cmp1),sort(b+1,b+n+1,cmp2);
    w.insert(1),w.insert(n),s.insert(n-1);
    for(int i=1,j=1;i<=n;++i) {
        while(j<=n&&b[j].f<=a[i].s) {
            if(b[j].id!=1&&b[j].id!=n)add(b[j].id);
            ++j;
        }
        ans[a[i].id]=*s.rbegin()<=a[i].d;
    }
    for(int i=1;i<=m;++i)printf("%d\n",ans[i]);
    return 0;
}