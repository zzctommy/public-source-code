#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
#define int long long
const int N=1e6+10;
char s[N];
int sum,ans;
signed main() {
	scanf("%s",s+1);int n=strlen(s+1);
	s[++n]='o';
	for(rint i=1,w=0;i<=n;++i) {
		if(s[i]=='v')++w;
		else sum+=(w>0?w-1:0),w=0;
	}
	for(rint i=1,w=0,now=0;i<=n;++i) {
		if(s[i]=='v')++w;
		else now+=(w>0?w-1:0),w=0,ans+=now*(sum-now); 
	}
	printf("%lld\n",ans);
	return 0;
}