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
#define zky 1000000007
#define N 100009
int n,k,a[N],dp[N][3],c[N];
int head[N],num_edge;
struct edge {
	int to,nxt;
}e[N<<1];
void addedge(int from,int to) {
	++num_edge;
	e[num_edge].nxt=head[from];
	e[num_edge].to=to;
	head[from]=num_edge;
}
void dfs(int u,int ft) {
    if(~c[u])dp[u][c[u]]=1;
    else dp[u][0]=dp[u][1]=dp[u][2]=1;
    for(int i=head[u];i;i=e[i].nxt) {
        int v=e[i].to;
        if(v==ft)continue;
        dfs(v,u);
        if(~c[u]) {
            dp[u][c[u]]=1ll*dp[u][c[u]]*(dp[v][(c[u]+1)%3]+dp[v][(c[u]+2)%3])%zky;
        } else {
            dp[u][0]=1ll*dp[u][0]*(dp[v][1]+dp[v][2])%zky;
            dp[u][1]=1ll*dp[u][1]*(dp[v][0]+dp[v][2])%zky;
            dp[u][2]=1ll*dp[u][2]*(dp[v][0]+dp[v][1])%zky;
        }
    }
}
signed main() {
    n=rd(),k=rd();
    for(int i=1;i<n;++i){
        int x=rd(),y=rd();
        addedge(x,y),addedge(y,x);
    }
    memset(c,-1,sizeof(c));
    for(int i=1;i<=k;++i) {
        int x=rd(),y=rd();
        c[x]=y-1;
    }
    dfs(1,0);
    printf("%d\n",((dp[1][0]+dp[1][1])%zky+dp[1][2])%zky);
    return 0;
}