#include<bits/stdc++.h>
using namespace std;
string s="0123456789ABCDEFGHIJK"; 
void orz(int n,int r)
{
	if(n==0)return;
	int m=n%r;
	if(m<0)m-=r,n+=r;
	orz(n/r,r);
	printf("%c",s[m]);
}
int main()
{
	int base,num;
	scanf("%d%d",&num,&base);
	printf("%d=",num);
	orz(num,base);
	printf("(base%d)\n",base);
	return 0;
 } 