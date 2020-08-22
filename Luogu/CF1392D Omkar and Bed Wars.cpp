#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=200010;
const int inf=1e9+7;
int n,T,a[N],ans,st;
char s[N];
void Main() {
	n=rd(),ans=0,st=-1;
	scanf("%s",s);
	for(int i=0;i<n-1;++i)if(s[i]!=s[i+1]){st=i+1;break;}
	if(!~st)return printf("%lld\n",(n+2)/3),void();
	for(int i=st,j=1;j<=n;++i,++j)a[j]=s[i%n]=='R';
	a[n+1]=a[1];
	for(int i=1,len=0;i<=n;++i) {
		++len;
		if(a[i]!=a[i+1]) ans+=len/3,len=0;
	}
		
	printf("%lld\n",ans);
}
signed main() {for(T=rd();T;--T)Main();}