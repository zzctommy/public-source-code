#pragma GCC optimize(2)
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
const int N=1e5+10;
const int M=320;
int n,c,m,a[N],bel[N],L[N],R[N],cnt[M][N],val[M][M],num,size,tmp[N],lastans;
void init() {
    size=sqrt(n),num=(n-1)/size+1;
    for(rint i=1;i<=num;++i)L[i]=(i-1)*size+1,R[i]=i*size;R[num]=n;
    for(rint i=1;i<=num;++i)
        for(rint j=L[i];j<=R[i];++j)
            bel[j]=i;
    for(rint i=1;i<=num;++i) {
        int now=0;
        for(rint j=L[i];j<=n;++j) {
            ++cnt[i][a[j]];
            if(cnt[i][a[j]]>1&&(cnt[i][a[j]]&1))--now;
            else if(!(cnt[i][a[j]]&1))++now;
            if(R[bel[j]]==j)val[i][bel[j]]=now;
        }
    }
}
int brute(int l,int r) {
    int res=0;
    for(rint i=l;i<=r;++i) {
        ++tmp[a[i]];
        if(tmp[a[i]]>1&&(tmp[a[i]]&1))--res;
        else if(!(tmp[a[i]]&1))++res;
    }
    for(rint i=l;i<=r;++i)--tmp[a[i]];
    return res;
}
#define app(x,y,z) (cnt[x][z]-cnt[y+1][z])
int query(int l,int r) {
    if(bel[r]-bel[l]<2)return brute(l,r);
    int res=val[bel[l]+1][bel[r]-1];
    for(rint i=l;i<=R[bel[l]];++i) {
        ++tmp[a[i]];
        int fyy=tmp[a[i]]+app(bel[l]+1,bel[r]-1,a[i]);
        if(fyy>1&&(fyy&1))--res;
        else if(!(fyy&1))++res;
    }
    for(rint i=L[bel[r]];i<=r;++i) {
        ++tmp[a[i]];
        int fyy=tmp[a[i]]+app(bel[l]+1,bel[r]-1,a[i]);
        if(fyy>1&&(fyy&1))--res;
        else if(!(fyy&1))++res;
    }
    for(rint i=l;i<=R[bel[l]];++i)--tmp[a[i]];
    for(rint i=L[bel[r]];i<=r;++i)--tmp[a[i]];
    return res;
}
signed main() {
    n=rd(),c=rd(),m=rd();
    for(rint i=1;i<=n;++i)a[i]=rd();
    init();
    while(m--) {
        int l=(rd()+lastans)%n+1,r=(rd()+lastans)%n+1;
        if(l>r)l^=r^=l^=r;
        printf("%d\n",lastans=query(l,r));
    }
    return 0;
}
