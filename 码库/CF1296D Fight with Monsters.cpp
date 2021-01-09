#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,a,b,k,x[N],ans,sum;
int main()
{
	scanf("%d%d%d%d",&n,&a,&b,&k);
	for(int i=1,hp,tmp;i<=n;++i)
	{
		scanf("%d",&hp);
		tmp=(hp-1)%(a+b)+1;
		x[i]=tmp/a;
		if(x[i]*a==tmp)--x[i];
	}
	sort(x+1,x+n+1);
	for(int i=1;i<=n;++i)
	{
		sum+=x[i];
		if(sum>k)break;
		++ans;
	}
	printf("%d\n",ans);
	return 0;
}