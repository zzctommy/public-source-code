#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=200005;
const int K=50;
int n,k,p,a[N],b[N];
int s[K][N];
LL ans;
signed main(){
	n=read(),k=read(),p=read();
	for(int i=1,lst=-1;i<=n;++i){
		a[i]=read(),b[i]=read();
		for(int j=0;j<k;++j)s[j][i]=s[j][i-1];
		s[a[i]][i]=s[a[i]][i-1]+1;
		if(b[i]<=p)lst=i,ans+=s[a[i]][i-1];
		else if(~lst)ans+=s[a[i]][lst];
	}
	printf("%lld\n",ans);
	return 0;
}