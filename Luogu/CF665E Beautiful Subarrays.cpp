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
const int N=1000005;
const int M=N*31;
int n,k,a[N],ch[M][2],tot=1,siz[M];
LL ans;
void insert(int x) {
	int u=1;
	for(int i=30;~i;--i) {
		int c=x>>i&1;
		if(!ch[u][c])ch[u][c]=++tot;
		u=ch[u][c],++siz[u];
	}
}
int query(int x) {
	int u=1,res=0,i;
	for(i=30;~i;--i) {
		int c=x>>i&1;
		if(k>>i&1)u=ch[u][!c];
		else res+=siz[ch[u][!c]],u=ch[u][c];
	}
	res+=siz[u];
	return res;
}
signed main() {
	n=rd(),k=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	for(int i=1;i<=n;++i)a[i]^=a[i-1];
	for(int i=1;i<=n;++i)insert(a[i-1]),ans+=query(a[i]);
	printf("%lld\n",ans);
	return 0;
}
