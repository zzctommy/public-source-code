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
		int a=read(),b=read();
		printf("%d\n",a+b-(a&b)*2);
	}
}