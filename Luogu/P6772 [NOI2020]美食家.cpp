#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define F(i,l,r) for(int i=l;i<=r;++i)
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=53;
const int K=205;
const int L=255;
const LL inf=1e15;
int n,m,T,k,l,c[N];
LL ans[L],t[L];
struct Matrix {
    LL a[L][L];
    LL* operator [] (const int&k){return a[k];}
}mp[33];
struct node {int t,x,y;}pty[K];
int f(int x,int y){return x+y*n;}
inline bool cmp(const node &a,const node &b) {
    return a.t<b.t;
}
signed main() {
    n=rd(),m=rd(),T=rd(),k=rd(),l=5*n;
	F(i,0,30)F(j,1,l)F(k,1,l)mp[i][j][k]=-inf;
    for(int i=1;i<=n;++i) {
        for(int j=4;j>0;--j)mp[0][f(i,j)][f(i,j-1)]=0;
        c[i]=rd();
    }
    ans[1]=0;for(int i=2;i<=l;++i)ans[i]=-inf;
    for(int i=1;i<=m;++i) {
        int x=rd(),y=rd(),z=rd();
        mp[0][y][f(x,z-1)]=c[x];
    }
    for(int r=1;r<=30;++r)
        F(i,1,l)F(k,1,l)F(j,1,l)mp[r][i][j]=max(mp[r][i][j],mp[r-1][i][k]+mp[r-1][k][j]);
    for(int i=1;i<=k;++i)pty[i].t=rd(),pty[i].x=rd(),pty[i].y=rd();
    sort(pty+1,pty+k+1,cmp);
	pty[k+1].t=T;
    for(int z=1;z<=k+1;++z) {
        int d=pty[z].t-pty[z-1].t;
        for(int r=0;d;++r,d>>=1)
            if(d&1) {
				F(i,1,l)t[i]=-inf;
				F(i,1,l)F(k,1,l)t[i]=max(t[i],mp[r][i][k]+ans[k]);
				F(i,1,l)ans[i]=t[i];
			}
        ans[pty[z].x]+=pty[z].y;
    }
	ans[1]+=c[1];
    if(ans[1]<0)puts("-1");
    else printf("%lld\n",ans[1]);
    return 0;
}