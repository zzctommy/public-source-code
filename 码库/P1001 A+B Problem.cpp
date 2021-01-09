#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void write(int a)
{
	if(a>9)write(a/10);
	putchar(a%10+'0');
}
int main()
{
	int a,b;
	a=read();
	b=read();
	write(a+b);
} 