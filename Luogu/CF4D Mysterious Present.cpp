#include<bits/stdc++.h>
using namespace std;
int n,w,v,cnt,dp[5005],pre[5005],fir,ans;
struct node{
	int x,y,id;
}a[5005];
bool cmp(node a,node b)
{
	if(a.x!=b.x)return a.x<b.x;
	return a.y<b.y;
}
void print(int u)
{
	if(u==-1)return;
	print(pre[u]);
	printf("%d ",a[u].id);
}
int main()
{
	scanf("%d%d%d",&n,&w,&v);
	for(int i=1;i<=n;i++)
	{
		int wi,vi;
		scanf("%d%d",&wi,&vi);
		if(wi>w&&vi>v)
		{
			a[++cnt].x=wi;
			a[cnt].y=vi;
			a[cnt].id=i;
		}
	}
	if(!cnt){puts("0");return 0;}
	sort(a+1,a+cnt+1,cmp);
	for(int i=1;i<=n;i++)
		dp[i]=1,pre[i]=-1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<i;j++)
		{
			if(a[i].x>a[j].x&&a[i].y>a[j].y&&dp[i]<dp[j]+1)
			{
				pre[i]=j;
				dp[i]=dp[j]+1;
			}
		}
		if(dp[i]>ans)
		{
			ans=dp[i];
			fir=i;
		}
	}
	printf("%d\n",ans);
	print(fir);
	return 0;
}