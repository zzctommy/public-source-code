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
bool vis[N];
int n,m;
vector<int>v;
void Main() {
	n=rd(),m=rd();
	for(int i=1;i<=n*3;++i)vis[i]=0;
	v.clear();
	for(int i=1;i<=m;++i) {
		int x=rd(),y=rd();
		if(!vis[x]&&!vis[y])vis[x]=vis[y]=1,v.push_back(i);
	}
	if(v.size()>=n){
		puts("Matching");
		for(int i=0;i<n;++i)printf("%d ",v[i]);
	} else {
		puts("IndSet");
		for(int i=1,j=1;j<=n;++i)if(!vis[i])printf("%d ",i),++j;
	}
	puts("");
}
signed main() {
	for(int T=rd();T;--T)Main();
}
