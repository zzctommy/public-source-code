#include <bits/stdc++.h>
using namespace std;
int main() {
	char k,c;
	int a=0,b=0,x=0;
	double ans;
	int now=1,f=1,r=0;
	while(scanf("%c",&c)==1)
	{
		if(c==10)break;
		if(c=='-')
		{
			b+=now*f*x;
			x=0;
			f=-1;
			r=0;
		}
		if(c=='+')
		{
			b+=now*f*x;
			f=1;
			x=0;
			r=0;
		}
		if(c=='=')
		{
			b+=now*f*x;
			now=-1;
			f=1;
			x=0;
			r=0;
		}
		if(c>='0'&&c<='9')
		{
			x=x*10+c-'0';
			r=1;
		}
		if(c>='a'&&c<='z')
		{
			k=c;
			if(r)
			{
				a+=now*f*x;
				x=0;
			}
			else 
			{
				a+=now*f;
			}
		}
	}
	b+=now*f*x;
	ans=-b*1.0/a;
	if(ans==-0.0)ans=0;
	if(a==0&&b!=0)puts("NO SOLUTION");
	else if(a==0&&b==0)puts("THE NUM OF SOLUTION IS INF");
	else printf("%c=%0.3lf\n",k,ans);
	return 0;
}
