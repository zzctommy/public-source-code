#include<bits/stdc++.h>
using namespace std;
#define rint register int
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
#define N 200010
#define C 200000
int n,a[N];
long long ans,sum;
vector<int>v[N*3];
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i)a[i]=rd(),v[a[i]-i+C].push_back(i);
	for(rint i=0;i<=C*3;++i) {
		sum=0;
		for(rint j=0;j<v[i].size();++j)
			sum+=a[v[i][j]];
		ans=max(ans,sum);
	}
	printf("%lld\n",ans);
	return 0;
}