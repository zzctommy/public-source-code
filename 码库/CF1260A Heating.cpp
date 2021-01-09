#include<bits/stdc++.h>
using namespace std;
int n,a,b,ans;
int main() {
	scanf("%d",&n);
	while(n--) {
		ans=0;
		scanf("%d%d",&a,&b);
		int tmp=b/a;
		int sum=b-tmp*a;
		ans+=(a-sum)*tmp*tmp;
		ans+=sum*(tmp+1)*(tmp+1);
		printf("%d\n",ans);
	}
	return 0;
} 