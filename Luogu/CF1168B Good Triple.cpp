#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=300005;
int n;
LL ans;
char s[N];
signed main() {
	scanf("%s",s+1),n=strlen(s+1);
	for(int i=n,r=n+1;i>=1;--i) {
		for(int j=1;i+j*2<=n;++j)
			if(s[i]==s[i+j]&&s[i]==s[i+j*2]){r=min(r,i+j*2);break;}
		ans+=n-r+1;
	}
	printf("%lld\n",ans);
}
