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
int rdc() {
	char ch=getchar();
	while(ch!='0'&&ch!='1'&&ch!='S'&&ch!='F')ch=getchar();
	if(ch=='0')return 0;
	if(ch=='1')return 1;
	return -1;
}
int n;
char s[100005];
signed main(){
	scanf("%s",s),n=strlen(s);
	puts("3");
	printf("R %d\n",n-1);
	printf("L %d\n",n);
	printf("L 2\n");
	return 0;
}