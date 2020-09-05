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
int n,h[N],val[N],lef[N],numlef;
LL dp[N],f[N],ans=1e15;
vector<int>g[N];
char s[30];
void dfs1(int u) {
    if(lef[u])h[u]=1;
    for(int v:g[u])dfs1(v),h[u]+=h[v],f[u]+=f[v]+h[v]*val[v];
}
void dfs2(int u) {
    for(int v:g[u]) {
        dp[v]=dp[u]-h[v]*val[v]+3*(numlef-h[v]);
        dfs2(v);
    }
}
signed main() {
    n=rd();
    for(int i=1,j,k;i<=n;++i) {
        scanf("%s",s);
        val[i]=strlen(s)+1;
        for(j=rd(),k=1;k<=j;++k)g[i].pb(rd());
        if(!j)lef[i]=1,++numlef;
    }
    dfs1(1),dp[1]=f[1],dfs2(1);
    for(int i=1;i<=n;++i)ans=min(ans,dp[i]);
    printf("%lld\n",ans-numlef);
    return 0;
}