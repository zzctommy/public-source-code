#include<bits/stdc++.h>
using namespace std;
string st[25];
int orz[25][25];
int vis[25];
int ans=-1,mx=0,n;
char ch;
int dalao(int x,int y)
{
	bool f=true;
	int ky=0;
	for(int k=st[x].length()-1;k>=1;k--)
	{
		for(int j=k;j<st[x].length();j++)
		{
			if(st[x][j]!=st[y][ky++])
			{
				f=false;break;
			}
		}
		if(f)
		{
			return st[x].length()-k;
		}
		else
		{
			f=true;
			ky=0;
		}
	}
	return 0;
}
void dfs(int x)
{
	bool flag=false;
	for(int i=1;i<=n;i++)
	{
		if(orz[x][i]==0)continue;
		if(vis[i]==2)continue;
		if(orz[x][i]==st[x].length()||orz[x][i]==st[i].length())continue;
		vis[i]++;
		mx+=st[i].length()-orz[x][i];
		flag=true;
		dfs(i);
		vis[i]--;
		mx-=st[i].length()-orz[x][i];	
	}
	if(!flag)ans=max(mx,ans);
	return;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		cin>>st[i];
	cin>>ch;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		orz[i][j]=dalao(i,j);
	for(int i=1;i<=n;i++)
	{
		if(st[i][0]==ch)
		{
			vis[i]++;
			mx=st[i].length();
			dfs(i);
			vis[i]--;
		}
	}
	cout<<ans<<endl;
	return 0;
} 
