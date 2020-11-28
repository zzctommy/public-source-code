#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define N 2100005
int h,g,n,m,a[N],ans[N],tot;
LL sum;
#define lc (p<<1)
#define rc (p<<1|1)
int find(int p){
	if(!a[lc]&&!a[rc])return p;
	if(a[lc]>a[rc])return find(lc);
	else return find(rc);
}
void f(int p){
	if(!a[lc]&&!a[rc])return a[p]=0,void();
	if(a[lc]>a[rc])a[p]=a[lc],f(lc);
	else a[p]=a[rc],f(rc);
}
void Main(){
	n=(1<<(h=read()))-1,m=(1<<(g=read()))-1;
	tot=sum=0,fill(a,a+(n*2)+2,0);
	for(int i=1;i<=n;++i)a[i]=read(),sum+=a[i];
	for(int i=1;i<=m;++i)
		while(find(i)>m)ans[++tot]=i,sum-=a[i],f(i);
	printf("%lld\n",sum);
	for(int i=1;i<=tot;++i)printf("%d ",ans[i]);
	puts("");
}
signed main(){for(int T=read();T;--T)Main();}