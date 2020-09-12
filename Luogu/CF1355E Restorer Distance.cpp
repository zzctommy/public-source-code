#include<bits/stdc++.h>
using namespace std;
#define rint register int
typedef long long LL;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
const int N=100010;
int n,a,b,c,hi;
int h[N];
int check(int x) {
 	int sum1=0,sum2=0;
  	for(rint i=1;i<=n;++i)
   		if(x>h[i])sum1+=x-h[i];
   		else sum2+=h[i]-x;
   	int tmp=min(sum1,sum2);
  	return tmp*c+(sum1-tmp)*a+(sum2-tmp)*b; 
}
signed main() {
  	n=rd(),a=rd(),b=rd(),c=rd(),c=min(a+b,c);
   	for(rint i=1;i<=n;++i)h[i]=rd(),hi=max(hi,h[i]);
   	int l=0,r=hi;
   	while(l<r) {
   		int mid=(l+r)>>1;
   		if(check(mid)>check(mid+1))l=mid+1;
   		else r=mid;
   	} 
   	printf("%lld\n",check(l));
   	return 0;
}