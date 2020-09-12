#include <bits/stdc++.h>
using namespace std;
int l,n,p,ans1,ans2;
int main() {
	scanf("%d%d",&l,&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&p);
		ans1=max(ans1,min(l-p+1,p));
		ans2=max(ans2,max(l-p+1,p));
	}
	printf("%d %d\n",ans1,ans2);
	return 0;
}