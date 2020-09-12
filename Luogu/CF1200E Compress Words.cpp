#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=2010010;
int n,m,p[N],len,Len;
char s[N],t[N],ans[N];
signed main() {
	n=rd();
	for(rint T=1;T<=n;++T) {
		scanf("%s",t+1),len=strlen(t+1);t[++len]='|';
		int top=0;
		for(rint i=1;i<=len;++i)s[++top]=t[i];
		int tmp=min(len,Len);
		for(rint i=Len-tmp+1;i<=Len;++i)s[++top]=ans[i];
		//for(rint i=1;i<=top;++i)cout<<s[i];cout<<endl;
		for(rint i=2,j=0;i<=top;++i) {
			while(j&&s[j+1]!=s[i])j=p[j];
			if(s[j+1]==s[i])++j;p[i]=j;
		}
		for(rint i=p[top]+1;i<len;++i)ans[++Len]=t[i];
	}
	for(rint i=1;i<=Len;++i)putchar(ans[i]);
	return 0;
}