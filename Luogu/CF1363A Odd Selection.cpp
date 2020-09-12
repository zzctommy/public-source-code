#include<bits/stdc++.h>
using namespace std;
int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
#define N 1009
int n,x,s[2];
void Main() {
	n=rd(),x=rd();
	s[0]=s[1]=0;
	for(int i=1;i<=n;++i)++s[rd()%2];
	if(x==n)puts(s[1]%2==1?"Yes":"No");
	else if(s[1]&&s[0])puts("Yes");
	else if(s[1]&&!s[0])puts(x&1?"Yes":"No");
	else if(!s[1]&&s[0])puts("No");
}
signed main() {
	for(int T=rd();T;--T)Main();
}