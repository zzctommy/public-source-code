#include<bits/stdc++.h>
using namespace std;
#define rint register int
#define int long long
typedef long long LL;
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
int k,p,pw[20],ans;
int rev(int x) {
	int res=0;
	while(x)res=res*10+x%10,x/=10;
	return res;
}
signed main() {
	k=rd(),p=rd();
	pw[0]=1;for(rint i=1;i<=9;++i)pw[i]=pw[i-1]*10;
	for(rint i=1,j=0;i<=k;++i) {
		while(i>=pw[j])++j;
		ans=(ans+pw[j]*i+rev(i))%p;
	}
	printf("%lld\n",ans);
	return 0;
}