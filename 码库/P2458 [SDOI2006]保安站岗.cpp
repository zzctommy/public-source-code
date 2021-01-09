#include<bits/stdc++.h>
using namespace std;
const int N=2005;
int f[N][3],v[N],root=1,n;
vector<int>g[N];
bool vis[N];
//f[i][0]当前节点父亲监视
//f[i][1]当前节点儿子监视
//f[i][2]当前节点放守卫
void DP(int u)
{
    int d=1000000007;
    for(int i=0;i<g[u].size();++i)
    {
        int v=g[u][i];
        DP(v);
        f[u][0]+=min(f[v][1],f[v][2]);
        f[u][1]+=min(f[v][1],f[v][2]);
        d=min(d,f[v][2]-min(f[v][2],f[v][1]));
        f[u][2]+=min(f[v][0],min(f[v][1],f[v][2]));
    }
    f[u][2]+=v[u];
    f[u][1]+=d;
}
int main()
{
    scanf("%d",&n);
    for(int i=1,m,x;i<=n;++i)
    {
        scanf("%d",&x);
        scanf("%d%d",&v[x],&m);
        for(int j=1,y;j<=m;++j)
        {
            scanf("%d",&y);
            g[x].push_back(y);
            vis[y]=true;
        }
    }
    while(vis[root])++root;
    DP(root);
    printf("%d\n",min(f[root][1],f[root][2]));
    return 0;
}
