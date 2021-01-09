//Orz cyn2006
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
signed main(){
	int a=read(),b=read(),c=read(),d=read();
	printf("%d\n",(b+d+max(a,c))*2+4);
	return 0;
}