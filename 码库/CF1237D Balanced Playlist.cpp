#include<bits/stdc++.h>
using namespace std;
#define rint register int
#define N (100010)
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
int n,a[N*3],l=1,r=0,p[N*3],q[N*3],ans[N*3],mx,mi=1000000007;
int main() {
	n=rd();
	for(rint i=1;i<=n;++i) {
		a[i]=rd(),a[i+n]=a[i+n*2]=a[i];
		mx=max(mx,a[i]),mi=min(mi,a[i]);
	}
	if(mi*2>=mx) {
		for(rint i=1;i<=n;++i)
			printf("-1 ");
		return puts(""),0;
	}
	for(rint i=1;i<=n*3;++i) {
		while(l<=r&&a[i]>=q[r])--r;
		q[++r]=a[i],p[r]=i;
		while(l<=r&&q[l]>a[i]*2) ans[p[l]]=i-p[l],++l;
	} 
	for(rint i=3*n;i>=1;--i)
		if(!ans[i])ans[i]=ans[i+1]+1;
	for(rint i=1;i<=n;++i)
		printf("%d ",ans[i]);
	return 0;
}