#include<bits/stdc++.h>
using namespace std;
#define rint register int
const int N=51;
int n,mp[N][N],cans,cnum[N];
inline int read()
{
	char ch=getchar();
	while(ch!='1'&&ch!='0')ch=getchar();
	return ch-'0';
}
bool dfs(int step,int *e,int nume)
{
	if(step>cans){cans=step;return true;}
	int e1[N],nume1=0;
	for(rint i=1;i<=nume;++i)
	{
		if(step+nume-i+1<=cans)break;
		if(step+cnum[e[i]]<=cans)break;
		nume1=0;
		for(rint j=i+1;j<=nume;++j)
		if(mp[e[i]][e[j]])e1[++nume1]=e[j];
		if(dfs(step+1,e1,nume1))return true;
	}
	return false;
}
inline void maxclique()
{
	int e[N],nume;
	cnum[n]=1;cans=1;
	for(rint i=n-1;i>=1;--i)
	{
		nume=0;cnum[i]=1;
		for(rint j=i+1;j<=n;j++)
			if(mp[i][j])e[++nume]=j;
		dfs(1,e,nume);
		cnum[i]=cans;
	}
}
int main()
{
	while(scanf("%d",&n)==1)
	{
		if(!n)return 0;
		memset(mp,0,sizeof(mp));
		for(rint i=1;i<=n;++i)
			for(rint j=1;j<=n;++j)
				mp[i][j]=read();
		maxclique();
		printf("%d\n",cans);
	}
}