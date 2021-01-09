#include<bits/stdc++.h>
using namespace std;
int power(int n,int k)
{
	int base=n,ans=1;
	while(k>0)
	{
		if(k&1)ans*=base;
		base*=base;
		k>>=1;
	}
	return ans;
}
void dfs(int n)
{
	int x;
	for(int i=0;;i++)
	{
		if(power(2,i)>n)
		{
			x=i-1;
			break;
		}
	}
	if(x==0)printf("2(0)");
	if(x==1)printf("2");
	if(x>1)
	{
		printf("2(");
		dfs(x);
		printf(")");
	}
	if(n!=power(2,x))
	{
		printf("+");
		dfs(n-power(2,x));
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	dfs(n);
	return 0;
}