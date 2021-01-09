//Orz cyn2006
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 105
int n,a[N],ans[N];
signed main(){
	n=read();
	for(int i=1;i<=n;++i)a[i]=read();
	sort(a+1,a+n+1);
	int l=1,r=n;
	ans[1]=a[1],ans[n]=a[2];
	for(int i=3;i<=n;++i){
		if(a[i]-ans[l]<a[i]-ans[r])ans[--r]=a[i];
		else ans[++l]=a[i];
	}
	for(int i=1;i<=n;++i)printf("%lld ",ans[i]);
	puts("");
	return 0;
}