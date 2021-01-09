#include<bits/stdc++.h>
using namespace std;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
double log(int x,int y) {
	return 1.*log(y)/log(x);
}
signed main() {
	int x=rd(),y=rd();
	if(x==1||y==1) {
		if(x==y)puts("=");
		else puts(x==1?"<":">");
		return 0;
	}
	double t=y/log(x,y);
	if(t==x)puts("=");
	else if(t>x)puts(">");
	else puts("<");
}