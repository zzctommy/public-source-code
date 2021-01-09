#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=105;
const int M=25;
const int inf=1000000007;
int n,m,k,E,d;
int dp[N];
int head[M],num_edge;
int dis[M],vis[M];
bitset<N>bs[M];
bitset<M>book;
struct node {
	int p,op;
	node(){p=op=0;}
	node(int p_,int o_){p=p_,op=o_;}
};
struct edge {
	int nxt,to,val;
}e[M*M*2];
struct Dij{
	int u,dis;
	Dij(){u=dis=0;}
	Dij(int u_,int d_){u=u_,dis=d_;}
	bool operator < (const Dij &rhs)const{return dis>rhs.dis;}
};
void addedge(int fr,int to,int val) {
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	e[num_edge].val=val;
	head[fr]=num_edge;
}
bool cmp(const node &a,const node &b) {
	return a.op<b.op;
}
int dij() {
	priority_queue<Dij>q;q.push(Dij(1,0));
	for(int i=1;i<=m;++i)dis[i]=inf,vis[i]=0;
	dis[1]=0;
	while(!q.empty()) {
		Dij now=q.top();q.pop();
		int u=now.u;
		if(vis[u])continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt) {
			int v=e[i].to;
			if(book[v])continue;
			if(dis[v]>dis[u]+e[i].val) {
				dis[v]=dis[u]+e[i].val;
				if(!vis[v])q.push(Dij(v,dis[v]));
			}
		}
	}
	return dis[m];
}
signed main() {
	n=rd(),m=rd(),k=rd(),E=rd();
	for(int i=1;i<=E;++i) {
		int x=rd(),y=rd(),z=rd();
		addedge(x,y,z),addedge(y,x,z);
	}
	d=rd();
	for(int i=1;i<=d;++i) {
		int p=rd(),a=rd(),b=rd();
		for(int j=a;j<=b;++j)bs[p][j]=1;
	}
	dp[0]=-k;
	for(int i=1;i<=n;++i) {
		dp[i]=inf,book.reset();
		for(int j=i;j>0;--j) {
			for(int l=1;l<=m;++l)if(bs[l][j])book[l]=1;
			int t=dij();
			if(t==inf)break;
			dp[i]=min(dp[i],dp[j-1]+(i-j+1)*t+k);
		}
	}
	printf("%d\n",dp[n]);return 0;
}
