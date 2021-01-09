#include<bits/stdc++.h>
using namespace std;
int main()
{
	int num[10],sum;
	for(int i=123;i<=333;i++)
	{
		sum=0;
		memset(num,0,sizeof(num));
		int a=i,b=2*i,c=3*i;
		num[a%10]++;a/=10;
		num[a%10]++;a/=10;
		num[a%10]++;
		num[b%10]++;b/=10;
		num[b%10]++;b/=10;
		num[b%10]++;
		num[c%10]++;c/=10;
		num[c%10]++;c/=10;
		num[c%10]++;
		for(int j=1;j<=9;j++)
			if(num[j])sum++;
		if(sum==9)cout<<i<<" "<<i*2<<" "<<i*3<<endl;
	}
	return 0;
 } 