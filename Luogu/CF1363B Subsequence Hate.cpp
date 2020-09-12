#include<bits/stdc++.h>
using namespace std;
int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
#define N 1009
int n,s0[N],s1[N],ans;
char s[N];
void Main() {
	scanf("%s",s+1),n=strlen(s+1);
	for(int i=1;i<=n;++i)
		s0[i]=s0[i-1]+(s[i]=='0'),s1[i]=s1[i-1]+(s[i]=='1');
	ans=min(s0[n],s1[n]);
	for(int i=1;i<=n;++i)
		ans=min(ans,min(s0[i-1]+(s1[n]-s1[i]),s1[i-1]+(s0[n]-s0[i])));
	printf("%d\n",ans);
}
signed main() {
	for(int T=rd();T;--T)Main();
}