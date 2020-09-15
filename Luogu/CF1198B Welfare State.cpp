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
const int N=200005;
int n,q,a[N];
bool vis[N];
int opt[N],x[N],y[N];
signed main() {
	n=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	q=rd();
	for(int i=1;i<=q;++i) {
		opt[i]=rd(),x[i]=rd();
		if(opt[i]==1)y[i]=rd();
	}
	int val=0;
	for(int i=q;i>=1;--i) {
		if(opt[i]==1) {
			if(vis[x[i]])continue;
			a[x[i]]=max(y[i],val),vis[x[i]]=1;
		} else val=max(val,x[i]);
	}
	for(int i=1;i<=n;++i)if(!vis[i])a[i]=max(a[i],val);
	for(int i=1;i<=n;++i)printf("%d ",a[i]);
	return 0;
}
