#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
signed main(){
	for(int T=read();T;--T){
		int n=read();
		if(n&1)printf("%lld\n",1ll*n*(n-1)/2);
		else printf("%lld\n",1ll*n*(n-1)/2-n/2+1);
	}
}