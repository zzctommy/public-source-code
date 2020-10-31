#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define int long long
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
int c[10],x,y;
signed main(){
	for(int T=read();T;--T){
		x=read(),y=read();
		for(int i=1;i<=6;++i)c[i]=read();
		for(int j=1;j<=6;++j)
			for(int i=1;i<=6;++i)
				c[i]=min(c[i],c[i+1==7?1:i+1]+c[i-1==0?6:i-1]);
		if(x>=0&&y>=0)printf("%lld\n",c[1]*min(x,y)+(y-x>0?c[2]*(y-x):c[6]*(x-y)));
		else if(x>=0&&y<0)y=-y,printf("%lld\n",c[6]*x+c[5]*y);
		else if(x<0&&y>=0)x=-x,printf("%lld\n",c[3]*x+c[2]*y);
		else x=-x,y=-y,printf("%lld\n",c[4]*min(x,y)+(y-x>0?c[5]*(y-x):c[3]*(x-y)));
	}
}
/*
2
-3 1
1 3 5 7 9 11
1000000000 1000000000
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000

*/