#include<bits/stdc++.h>
using namespace std;
long long mmap[25][25],n,m,xx,yy,s[25][25];
int dx[9]={1,1,2,2,-1,-1,-2,-2};
int dy[9]={2,-2,1,-1,2,-2,1,-1};
bool ok(int x,int y)
{
	if(x>n||x<1||y>m||y<1)return false;
	return true;
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&xx,&yy);
	n++;m++;xx++;yy++;
	mmap[1][1]=1;
	s[xx][yy]=1;
	for(int i=0;i<8;i++)
	{
		if(ok(xx+dx[i],yy+dy[i]))s[xx+dx[i]][yy+dy[i]]=1;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(s[i][j])continue;
			mmap[i][j]=max(mmap[i][j],mmap[i-1][j]+mmap[i][j-1]);
		}
	printf("%lld\n",mmap[n][m]);
	return 0;
}