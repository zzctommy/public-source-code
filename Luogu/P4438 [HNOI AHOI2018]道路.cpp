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
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=20010;
int g[N][2];
int n,a[N],b[N],c[N];
int dep[N];
LL dp[N<<1][41][41];
void dfs(int u,int dep) {
    if(u>n) {
        for(int i=0;i<=dep;++i)
            for(int j=0;j<=dep-i;++j)
                dp[u][i][j]=1ll*c[u-n]*(a[u-n]+i)*(b[u-n]+j);
        return;
    }
    for(int i=0;i<2;++i)dfs(g[u][i],dep+1);
    for(int i=0;i<=dep;++i)
        for(int j=0;j<=dep-i;++j)
            dp[u][i][j]=min(dp[g[u][0]][i+1][j]+dp[g[u][1]][i][j],dp[g[u][0]][i][j]+dp[g[u][1]][i][j+1]);
}
signed main() {
    n=rd();
    for(int i=1;i<n;++i) {
        int x=rd(),y=rd();
        if(x>0)g[i][0]=x;
        else g[i][0]=n-x;
        if(y>0)g[i][1]=y;
        else g[i][1]=n-y;
    }
    for(int i=1;i<=n;++i)a[i]=rd(),b[i]=rd(),c[i]=rd();
    dfs(1,0);
    printf("%lld\n",dp[1][0][0]);
    return 0;
}