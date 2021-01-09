#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=1009;
char s[N],t[N];
int n,m,a[N],b[N];
signed main() {
	scanf("%s%s",s,t),n=strlen(s),m=strlen(t);
	if(n!=m)return puts("No"),0;
	for(int i=0;i<n;++i)
		a[i+1]=(s[i]=='a'||s[i]=='e'||s[i]=='o'||s[i]=='i'||s[i]=='u'),
		b[i+1]=(t[i]=='a'||t[i]=='e'||t[i]=='o'||t[i]=='i'||t[i]=='u');
	for(int i=1;i<=n;++i)if(a[i]!=b[i])return puts("No"),0;
	puts("Yes");return 0;
}