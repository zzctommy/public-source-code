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
const int N=200010;
int n,fa[N],dis[N],ans=1<<28;
int find(int x) {
	if(x==fa[x])return x;
	int fx=fa[x];
	fa[x]=find(fa[x]);
	dis[x]+=dis[fx];
	return fa[x];
}
void merge(int x,int y) {
	int fx=find(x),fy=find(y);
	if(fx==fy)ans=min(ans,dis[y]+1);
	else fa[fx]=fy,dis[x]=dis[y]+1;
}
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i)fa[i]=i;
	for(rint i=1;i<=n;++i)merge(i,rd());
	printf("%d\n",ans);
	return 0;
} 
