#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100005;
int n,a[N],siz[N],mx[N],r1,r2;
vector<int>e[N];
void dfs1(int u,int ft) {
	siz[u]=1,mx[u]=0;
	for(int v:e[u])if(v!=ft)
		dfs1(v,u),siz[u]+=siz[v],mx[u]=max(mx[u],siz[v]);
	mx[u]=max(mx[u],n-siz[u]);
	if(mx[u]<mx[r1])r1=u,r2=0;
	else if(mx[u]==mx[r1])r2=u;
}
void Main() {
	n=rd(),r1=r2=0,mx[0]=n;
	for(int i=1;i<=n;++i) {
		vector<int>fyyAKIOI;
		e[i].swap(fyyAKIOI); 
	}
	for(int i=1;i<n;++i) {
		int x=rd(),y=rd();
		e[x].push_back(y),e[y].push_back(x);
	}
	dfs1(1,0);
	if(!r2)printf("%d %d\n%d %d\n",1,e[1][0],1,e[1][0]);
	else  {
		int t=0;
		for(int v:e[r1])if(v!=r2){t=v;break;}
		printf("%d %d\n%d %d\n",t,r1,t,r2);
	}
}
signed main() {
	for(int T=rd();T;--T)Main();
}
