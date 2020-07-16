#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=1e5+10;
const int M=1e6+10;
int n,m,fib[N];
int minv,maxv;
int fa[N];
struct edge {
	int u,v,d;
}e[M];
bool cmp(const edge &a,const edge &b) {
	return a.d<b.d;
}
int find(int x) {
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
signed main() {
	n=rd(),m=rd();
	for(rint i=1;i<=m;++i)
		e[i].u=rd(),e[i].v=rd(),e[i].d=rd();
	sort(e+1,e+m+1,cmp);
	for(rint i=1;i<=n;++i)fa[i]=i;
	for(rint i=1;i<=m;++i) {
		int fx=find(e[i].u),fy=find(e[i].v);
		if(fx!=fy)fa[fx]=fy,minv+=e[i].d;
	}
	for(rint i=1;i<=n;++i)if(find(i)!=find(1))return puts("No"),0;
	for(rint i=1;i<=n;++i)fa[i]=i;
	for(rint i=m;i>=1;--i) {
		int fx=find(e[i].u),fy=find(e[i].v);
		if(fx!=fy)fa[fx]=fy,maxv+=e[i].d;
	}
	fib[1]=1,fib[2]=2;
	for(rint i=3;i<=44;++i)fib[i]=fib[i-1]+fib[i-2];
	for(rint i=1;i<=44;++i)if(minv<=fib[i]&&fib[i]<=maxv)return puts("Yes"),0;
	puts("No");return 0;
}
