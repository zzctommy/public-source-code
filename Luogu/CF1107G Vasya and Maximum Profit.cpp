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
#define N 300009
int n,a,ans;
int c[N],sc[N],d[N];
int lg[N],pw2[25];
int st[N],top,lp[N],rp[N];
struct ST_Table {
    int st[20][N];
    void init() {
        for(int i=1;i<=19;++i)
            for(int j=1;j+pw2[i]-1<=n;++j)
                st[i][j]=max(st[i-1][j],st[i-1][j+pw2[i-1]]);
    }
    int ask(int l,int r) {
		if(l>r)return 0;
        int x=lg[r-l+1];
        return max(st[x][l],st[x][r-pw2[x]+1]);
    }
}s[2];
void st_init() {
    lg[0]=-1,pw2[0]=1;
    for(int i=1;i<N;++i)lg[i]=lg[i>>1]+1;
    for(int i=1;i<=20;++i)pw2[i]=pw2[i-1]<<1;
}
signed main() {
    n=rd(),a=rd();
    st_init();
    for(int i=1;i<=n;++i)d[i]=rd(),sc[i]=sc[i-1]+(c[i]=rd());
    for(int i=1;i<n;++i)d[i]=(d[i+1]-d[i])*(d[i+1]-d[i]);
    for(int i=1;i<n;++i) {
        while(top&&d[st[top]]<d[i])rp[st[top--]]=i-1;
        lp[i]=st[top]+1,st[++top]=i;
    }
    while(top)rp[st[top--]]=n-1;
    for(int i=1;i<=n;++i)
        s[0].st[0][i]=sc[i-1]-a*(i-1),
        s[1].st[0][i]=a*(i+1)-sc[i+1];
    s[0].init(),s[1].init();
    for(int i=1;i<=n;++i)ans=max(ans,a-c[i]);
    for(int i=1;i<n;++i)
        ans=max(ans,s[0].ask(lp[i],i)+s[1].ask(i,rp[i])-d[i]);
    printf("%lld\n",ans);
    return 0;
}