#include<bits/stdc++.h>
using namespace std;
const int N=11;
int g[N][N],n,ans;
signed main() {
	scanf("%d",&n);
f\
o\
r(int i=1;i<=n;++i)
f\
o\
r(int j=1;j<=n;++j)scanf("%d",&g[i][j]);
f\
o\
r(int k=1;k<=n;++k)
f\
o\
r(int i=1;i<=n;++i)
f\
o\
r(int j=1;j<=n;++j)g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
f\
o\
r(int i=1;i<=n;++i)
f\
o\
r(int j=1;j<=n;++j)ans=max(ans,g[i][j]);
printf("%d\n",ans);
}
