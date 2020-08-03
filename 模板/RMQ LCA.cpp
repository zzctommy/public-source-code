#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
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
const int N=500010;
struct edge {
	int nxt,to;
}e[N<<1];
int n,m,S;
int mi[20][N<<1],id[20][N<<1],lg[N<<1],dfn[N],pw2[30],timer;
int head[N],num_edge;
void addedge(int fr,int to) {
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
void dfs(int u,int dep) {
	dfn[u]=++timer,mi[0][timer]=dep,id[0][timer]=u;
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(dfn[v])continue;
		dfs(v,dep+1),++timer,mi[0][timer]=dep,id[0][timer]=u;
	}
}
void init_ST() {
	lg[0]=-1,pw2[0]=1;
	for(int i=1;i<=(n<<1);++i)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=21;++i)pw2[i]=pw2[i-1]<<1;
	for(int i=1;i<=lg[n<<1];++i)
		for(int j=1;j<=(n<<1)-pw2[i]+1;++j) {
			int t=j+pw2[i-1];
			if(mi[i-1][j]<mi[i-1][t])mi[i][j]=mi[i-1][j],id[i][j]=id[i-1][j];
			else mi[i][j]=mi[i-1][t],id[i][j]=id[i-1][t];
		}
}
int ask(int x,int y) {
	int l=dfn[x],r=dfn[y];
	if(l>r)l^=r^=l^=r;
	int k=lg[r-l+1],t=r-pw2[k]+1;
	if(mi[k][l]<mi[k][t])return id[k][l];
	else return id[k][t];
}
signed main() {
	n=rd(),m=rd(),S=rd();
	for(int i=1;i<n;++i) {
		int x=rd(),y=rd();
		addedge(x,y),addedge(y,x);
	}
	dfs(S,1),init_ST();
	while(m--) {
		int x=rd(),y=rd();
		printf("%d\n",ask(x,y));
	}
	return 0;
}
