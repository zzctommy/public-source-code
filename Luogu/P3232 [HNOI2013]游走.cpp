#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=505;
int n,m,deg[N];
double G[N][N],F[N];
vector<int>g[N];
double ans,fyyAKCTS[N];
struct edge {
	int u,v;
}e[N*N];
void Gauss(int n) {
	for(int i=1;i<=n;++i) {
		int mx=i;
		for(int j=i;j<=n;++j)
			if(fabs(G[j][i])>fabs(G[mx][i]))mx=j;
		for(int j=1;j<=n+1;++j)swap(G[mx][j],G[i][j]);
		for(int j=1;j<=n;++j) {
			if(i==j)continue;
			double div=G[j][i]/G[i][i];
			for(int k=i+1;k<=n+1;++k)
				G[j][k]-=div*G[i][k];
		}
	}
	for(int i=1;i<=n;++i)F[i]=G[i][n+1]/G[i][i];
}
signed main() {
	n=rd(),m=rd();
	for(int i=1;i<=m;++i) {
		int x=rd(),y=rd();
		e[i].u=x,e[i].v=y,g[x].pb(y),g[y].pb(x),++deg[x],++deg[y];
	}
	for(int u=1;u<n;++u) {
		G[u][u]=-1;
		for(int v:g[u])if(v!=n)G[u][v]=1./deg[v];
	}
	G[1][n]=-1;
	Gauss(n-1);
	for(int i=1;i<=m;++i) {
		int u=e[i].u,v=e[i].v;
		if(u!=n)fyyAKCTS[i]+=F[u]/deg[u];
		if(v!=n)fyyAKCTS[i]+=F[v]/deg[v]; 
	}
	sort(fyyAKCTS+1,fyyAKCTS+m+1);
	for(int i=1,j=m;i<=m;--j,++i)ans+=1.*j*fyyAKCTS[i];
	printf("%.3lf\n",ans);
	return 0;
}
