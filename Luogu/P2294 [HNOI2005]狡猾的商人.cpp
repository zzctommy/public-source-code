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
const int N=109;
const int M=2200;
const int inf=10000007;
int n,m,S;
struct edge {
	int nxt,to,val;
}e[M];
int num_edge,head[N];
bitset<N>inq;
int num[N],dis[N];
void addedge(int fr,int to,int val) {
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	e[num_edge].val=val;
	head[fr]=num_edge;
}
void clear(){
	memset(head,0,sizeof(head));
	num_edge=0;
}
int spfa() {
	inq.reset();
	for(int i=0;i<=S;++i)num[i]=0,dis[i]=inf;
	queue<int>q;q.push(S),dis[S]=0;
	while(!q.empty()) {
		int u=q.front();q.pop(),inq[u]=0;
		for(int i=head[u];i;i=e[i].nxt) {
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].val) {
				dis[v]=dis[u]+e[i].val,++num[v];
				if(num[v]>n+2)return 0;
				if(!inq[v])q.push(v),inq[v]=1;
			}
		}
	}
	return 1;
}
void Main() {
	clear();
	n=rd(),m=rd(),S=n+1;
	for(int i=1;i<=m;++i) {
		int x=rd(),y=rd(),z=rd();
		addedge(x-1,y,z),addedge(y,x-1,-z);
	} 
	for(int i=0;i<=n;++i)addedge(S,i,-inf);
	puts(spfa()?"true":"false");
}
signed main() {for(int T=rd();T;--T)Main();}