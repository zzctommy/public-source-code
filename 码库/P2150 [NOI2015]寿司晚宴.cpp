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
#define int long long
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int pri[]={2,3,5,7,11,13,17,19};
int n,mod,ans;
int dp[260][260],f[260][260],g[260][260];
struct node {
    int mask,xf;
    node(){mask=xf=0;}
}a[510];
bool zhouAKngyang(const node &a,const node &b) {
    return a.xf<b.xf;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>mod;
    for(int i=2;i<=n;++i) {
        int t=i;
        for(int j=0;j<8;++j)
            if(t%pri[j]==0) {
                a[i].mask|=(1<<j);
                while(t%pri[j]==0)t/=pri[j];
            }
        a[i].xf=t;
    }
    sort(a+2,a+n+1,zhouAKngyang);
    dp[0][0]=1;
    for(int t=2;t<=n;++t) {
        if(a[t].xf==1||a[t].xf!=a[t-1].xf) {
            for(int i=0;i<(1<<8);++i)
                for(int j=0;j<(1<<8);++j)
                    f[i][j]=g[i][j]=dp[i][j];
        }
        for(int i=(1<<8)-1;~i;--i)
            for(int j=(1<<8)-1;~j;--j) {
                if(i&j)continue;
                if((j&a[t].mask)==0)f[i|a[t].mask][j]=(f[i|a[t].mask][j]+f[i][j])%mod;
                if((i&a[t].mask)==0)g[i][j|a[t].mask]=(g[i][j|a[t].mask]+g[i][j])%mod;
            }
        if(a[t].xf==1||a[t].xf!=a[t+1].xf) {
            for(int i=0;i<(1<<8);++i)
                for(int j=0;j<(1<<8);++j)
                    if((i&j)==0)dp[i][j]=(f[i][j]+g[i][j]-dp[i][j]+mod)%mod;
        }
    }
    for(int i=0;i<(1<<8);++i)
        for(int j=0;j<(1<<8);++j)
            if((i&j)==0)ans=(ans+dp[i][j])%mod;
    cout<<ans<<'\n';
    return 0;
}