#include<bits/stdc++.h>
using namespace std;
#define rint register int
const int N=55;
const int M=1300;
int n,num_edge,mp[N][N],head[N],p[N],ans;
bool check(int u,int num)
{
	for(rint i=1;i<=num;++i)
		if(!mp[p[i]][u])return false;
	return true;
}
void dfs(int u,int num)
{
	if(num>ans)ans=num;
	for(rint i=u+1;i<=n;++i)
	{
		if(check(i,num))
		{
			p[num+1]=i;
			dfs(i,num+1);
		}
	}
}
int main()
{
	while(scanf("%d",&n)==1)
	{
		if(!n)return 0;
		ans=0;
		memset(mp,0,sizeof(mp));
		for(rint i=1;i<=n;++i)
		{
			for(rint j=1;j<=n;++j)
			{
				scanf("%d",&mp[i][j]);
			}
		}
		for(rint i=1;i<=n;i++)
		{
			p[1]=i;
			dfs(i,1);
		}
		printf("%d\n",ans);
	}
}