#include<bits/stdc++.h>
using namespace std;
const int N=2005;
int T,n,a[N],sum; 
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		bool f[2];
		sum=f[0]=f[1]=0;
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
		{
			scanf("%d",&a[i]);
			f[a[i]%2]=true;
			sum+=a[i];
		}
		if(sum%2)puts("YES");
		else if(f[0]&&f[1])puts("YES");
		else puts("NO");
	}
	return 0;
 } 