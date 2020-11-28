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
#define N 10005
int n,a[N],b[N],ans;
signed main(){
	n=read();
	int lst=1;
	for(int i=1;i<=n;++i){
		a[i]=read(),b[i]=read();
		if(min(a[i],b[i])>=max(a[i-1],b[i-1]))ans+=min(a[i],b[i])-max(a[i-1],b[i-1])+lst;
		lst=a[i]!=b[i];
	}
	printf("%lld\n",ans);
	return 0;
}