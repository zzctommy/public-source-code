#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
#define db double
// #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
// char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=500010;
const int M=710;
int n,m;
int lsh[N],a[N],len;
int bel[N],L[M],R[M],size,num,val[M][M],bin[N],rev[N];
vector<int>f[N];
void init() {
    size=sqrt(n),num=(n-1)/size+1;
    for(int i=1;i<=num;++i)L[i]=R[i-1]+1,R[i]=i*size;
    R[num]=n;
    for(int i=1;i<=num;++i)
        for(int j=L[i];j<=R[i];++j)
            bel[j]=i;
    for(int i=1,mx;i<=num;++i) {
        mx=0,memset(bin,0,sizeof(bin));
        for(int j=L[i];j<=n;++j) {
            mx=max(mx,++bin[a[j]]);
            if(j==R[bel[j]])val[i][bel[j]]=mx;
        }
    }
}
int query(int l,int r) {
    if(bel[l]+1>=bel[r]) {
        int mx=0;
        for(int i=l;i<=r;++i)bin[a[i]]=0;
        for(int i=l;i<=r;++i)mx=max(mx,++bin[a[i]]);
        return mx;
    }
    int res=val[bel[l]+1][bel[r]-1];
    for(int i=l;i<=R[bel[l]];++i) {
        int p=rev[i];
        while(p+res<f[a[i]].size()&&f[a[i]][p+res]<=r)++res;
    }
    for(int i=L[bel[r]];i<=r;++i) {
        int p=rev[i];
        while(p-res>-1&&f[a[i]][p-res]>=l)++res;
    }
    return res;
}
signed main() {
    n=rd(),m=rd();
    for(int i=1;i<=n;++i)lsh[i]=a[i]=rd();
    sort(lsh+1,lsh+n+1),len=unique(lsh+1,lsh+n+1)-lsh-1;
    for(int i=1;i<=n;++i)
        a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh,f[a[i]].pb(i),rev[i]=f[a[i]].size()-1;
    init();
    while(m--) {
        int l=rd(),r=rd();
        printf("-%d\n",query(l,r));
    }
    return 0;
}