#include<bits/stdc++.h>
using namespace std;
#define rint register int
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
typedef long long LL;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=210;
const int M=40010;
struct edge {
    int to,nxt;
}e[N*N];
int num_edge,head[M];
int m,n,cas[N][N],ans;
int id[2][N][N],n1,n2,match[M];
bool vis[M];
void addedge(int from,int to) {
    ++num_edge,e[num_edge].nxt=head[from],e[num_edge].to=to,head[from]=num_edge;
}
int dfs(int u) {
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(!vis[v]) {
			vis[v]=1;
			if(!match[v]||dfs(match[v])) {
				match[v]=u;return 1;
			}
		}
	}
	return 0;
}
signed main() {
	m=rd(),n=rd();
	for(rint i=1;i<=m;++i)
		for(rint j=1;j<=n;++j)
			cas[i][j]=rd();
	for(rint i=1;i<=m;++i)cas[i][0]=2;
	for(rint i=1;i<=n;++i)cas[0][i]=2;
	for(rint i=1;i<=m;++i)
		for(rint j=1;j<=n;++j)
			if(cas[i][j]!=2) {
				if(cas[i][j-1]==2)id[0][i][j]=++n1;
				else id[0][i][j]=id[0][i][j-1];
			}
	for(rint j=1;j<=n;++j)
		for(rint i=1;i<=m;++i)
			if(cas[i][j]!=2) {
				if(cas[i-1][j]==2)id[1][i][j]=++n2;
				else id[1][i][j]=id[1][i-1][j];
			}
	for(rint i=1;i<=m;++i)
		for(rint j=1;j<=n;++j)
			if(!cas[i][j])addedge(id[0][i][j],id[1][i][j]);
	for(rint i=1;i<=n1;++i)
			fill(vis+1,vis+n2+1,0),ans+=dfs(i);
	printf("%d\n",ans);
	for(rint i=1;i<=m;++i)	
		for(rint j=1;j<=n;++j)
			if(!cas[i][j]&&id[0][i][j]==match[id[1][i][j]])printf("%d %d\n",i,j);
	return 0;
}
