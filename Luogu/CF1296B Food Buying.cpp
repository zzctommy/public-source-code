#include<bits/stdc++.h>
using namespace std;
const int N=2005;
int T,n,ans; 
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		ans=0;
		scanf("%d",&n);
		while(true)
		{
			int tmp=n/10;
			if(!tmp)break;
			n-=tmp*10;
			ans+=tmp*10;
			n+=tmp;
		}
		printf("%d\n",ans+n);
	}
	return 0;
 } 