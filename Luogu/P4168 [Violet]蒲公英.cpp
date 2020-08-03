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
const int N=40010;
const int M=210;
int n,m;
int lastans;
int lsh[N],a[N],len;
int bel[N],L[M],R[M],size,num,tim[N][M],val[M][M],bin[N],rev[N];
vector<int>f[N];
void init() {
    size=sqrt(n),num=(n-1)/size+1;
    for(int i=1;i<=num;++i)L[i]=R[i-1]+1,R[i]=i*size;
    R[num]=n;
    for(int i=1;i<=num;++i)
        for(int j=L[i];j<=R[i];++j)
            bel[j]=i;
    for(int i=1,mx;i<=num;++i) {
    	mx=0;
        for(int j=L[i];j<=n;++j) {
            ++bin[a[j]];
            if(bin[a[j]]>bin[mx])mx=a[j];
            else if(bin[a[j]]==bin[mx]&&a[j]<mx)mx=a[j];
            if(j==R[bel[j]])val[i][bel[j]]=mx;
        }
        memset(bin,0,sizeof(bin));
    }
    for(int i=1;i<=num;++i) {
    	for(int j=L[i];j<=R[i];++j)++tim[a[j]][i];
    	for(int j=1;j<=len;++j)tim[j][i]+=tim[j][i-1];
	}
}
int query(int l,int r) {
    if(bel[l]+1>=bel[r]) {
        int mx=0;
        for(int i=l;i<=r;++i) {
            ++bin[a[i]];
            if(bin[a[i]]>bin[mx])mx=a[i];
			else if(bin[a[i]]==bin[mx]&&a[i]<mx)mx=a[i];
        }
        for(int i=l;i<=r;++i)bin[a[i]]=0;
        return lsh[mx];
    }
    int bl=bel[l],br=bel[r];
    for(int i=l;i<=R[bl];++i)++bin[a[i]];
    for(int i=L[br];i<=r;++i)++bin[a[i]];
    int res=val[bl+1][br-1],mx=tim[res][br-1]-tim[res][bl]+bin[res];
    for(int i=l;i<=R[bl];++i) {
    	int t=tim[a[i]][br-1]-tim[a[i]][bl]+bin[a[i]];
    	if(t>mx)mx=t,res=a[i];
    	else if(t==mx&&res>a[i])res=a[i];
	}
	for(int i=L[br];i<=r;++i) {
    	int t=tim[a[i]][br-1]-tim[a[i]][bl]+bin[a[i]];
    	if(t>mx)mx=t,res=a[i];
    	else if(t==mx&&res>a[i])res=a[i];
	}
    for(int i=l;i<=R[bl];++i)bin[a[i]]=0;
    for(int i=L[br];i<=r;++i)bin[a[i]]=0;
	return lsh[res];
}
signed main() {
    n=rd(),m=rd();
    for(int i=1;i<=n;++i)lsh[i]=a[i]=rd();
    sort(lsh+1,lsh+n+1),len=unique(lsh+1,lsh+n+1)-lsh-1;
    for(int i=1;i<=n;++i)a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
    init();
    while(m--) {
        int l=(rd()+lastans-1)%n+1,r=(rd()+lastans-1)%n+1;
        if(l>r)l^=r^=l^=r;
        printf("%d\n",lastans=query(l,r));
    }
    return 0;
}
