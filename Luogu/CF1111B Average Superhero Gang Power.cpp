#include<bits/stdc++.h>
inline int rd(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch))f=(ch=='-'?0:f),ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define N 100009
int n,k,m,a[N];
typedef long long LL;
LL s[N];
typedef double db;
db ans;
signed main() {
	n=rd(),k=rd(),m=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	std::sort(a+1,a+n+1),std::reverse(a+1,a+n+1);
	for(int i=1;i<=n;++i)s[i]=s[i-1]+a[i];
	for(int i=n;i>=1&&n-i<=m;--i)
		ans=std::max(ans,1.*(s[i]+std::min(1ll*(m-(n-i)),1ll*k*i))/i);
	printf("%.10lf\n",ans);
	return 0;
}