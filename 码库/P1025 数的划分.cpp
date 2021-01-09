#include<bits/stdc++.h>
using namespace std;
int f[205][10];
int main()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		f[i][1]=f[i][0]=1;
	for(int i=2;i<=n;i++)
		for(int j=2;j<=k;j++)
		if(i>j)f[i][j]=f[i-1][j-1]+f[i-j][j];
		else f[i][j]=f[i-1][j-1];
	cout<<f[n][k]<<endl;
	return 0;
}
