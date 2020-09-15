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
const int N=1005;
char s[10];
int n,dis,rt,dep[N];
int head[N],num_edge;
vector<int>v[N],vec;
struct edge {
	int nxt,to;
}e[N<<1];
inline void addedge(int fr,int to) {
	++num_edge;
	e[num_edge].to=to;
	e[num_edge].nxt=head[fr];
	head[fr]=num_edge;
}
void dfs1(int u,int ft) {
	v[dep[u]].push_back(u);
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft)continue;
		dep[v]=dep[u]+1,dfs1(v,u);
	}
}
void dfs2(int u,int ft,int d) {
	if(d==dis)return vec.push_back(u),void();
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft)continue;
		dfs2(v,u,d+1);
	}
}
void Main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i)v[i].clear();
	memset(head,0,sizeof(head)),num_edge=0;
	vec.clear();
	for(int i=1;i<n;++i) {
		int x=rd(),y=rd();
		addedge(x,y),addedge(y,x);
	}
	printf("? %d",n);for(int i=1;i<=n;++i)printf(" %d",i);puts(""),fflush(stdout);
	scanf("%d%d",&rt,&dis);
	dep[rt]=0,dfs1(rt,0);
	int l=(dis+1)>>1,r=dis,ra,rb,t;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(!v[mid].size()){r=mid-1;continue;}
		printf("? %u",v[mid].size());for(int i:v[mid])printf(" %d",i);puts(""),fflush(stdout);
		scanf("%d%d",&ra,&rb);
		if(rb==dis)t=ra,l=mid+1;
		else r=mid-1;
	}
	dfs2(t,0,0);
	printf("? %u",vec.size());for(int i:vec)printf(" %d",i);puts(""),fflush(stdout);
	scanf("%d%d",&ra,&rb);
	printf("! %d %d\n",t,ra),fflush(stdout);
	scanf("%s",s);
}
signed main(){
	for(int T=rd();T;--T)Main();
}
