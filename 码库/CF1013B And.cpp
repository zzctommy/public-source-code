#include<bits/stdc++.h>
using namespace std;
int n,x,a[100005],b[100005],ans=3;
unordered_map<int,int>mp;
int main()
{
	scanf("%d%d",&n,&x);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]),b[i]=a[i]&x;
	for(int i=1;i<=n;++i)
		if(!mp[a[i]])mp[a[i]]=1;
		else{printf("0\n");return 0;}
	for(int i=1;i<=n;++i)
		if(mp[b[i]]&&a[i]^b[i])ans=min(ans,mp[b[i]]);
		else if(!mp[b[i]])mp[b[i]]=2;
	if(ans!=3)printf("%d\n",ans);
	else printf("-1\n");
	return 0;
}