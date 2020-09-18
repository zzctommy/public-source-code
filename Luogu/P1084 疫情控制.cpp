#include<bits/stdc++.h>
using namespace std;
#define pb(x) push_back(x)
typedef long long LL;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=50005;
int n,m,c[N],fa[17][N],dep[N],a[N];
bool tag[N],ned[N];
LL dis[N],ans=-1;
struct edge{
	int v,w;
	edge(){v=w=0;}
	edge(int v_,int w_){v=v_,w=w_;}
	inline bool operator < (const edge&p)const{return w<p.w;}
};
vector<edge>e[N];
struct node{
	int u;LL dis;
	node(){u=dis=0;}
	node(int u_,LL dis_){u=u_,dis=dis_;}
	inline bool operator < (const node&p)const{return dis<p.dis;}
};
void dfs1(int u,int ft){
	for(int i=1;1<<i<=dep[u];++i)fa[i][u]=fa[i-1][fa[i-1][u]];
	for(int i=0;i<e[u].size();++i){
		int v=e[u][i].v;if(v==ft)continue;
		dep[v]=dep[u]+1,dis[v]=dis[u]+e[u][i].w,fa[0][v]=u;
		dfs1(v,u);
	}
}
int dfs2(int u,int ft){
	if(tag[u])return 0;
	for(int i=0;i<e[u].size();++i){
		int v=e[u][i].v;if(v==ft)continue;
		if(dfs2(v,u))return 1;
	}
	return e[u].size()<2;
}
bool check(LL k){
	memset(tag,0,sizeof(tag));
	memset(ned,0,sizeof(ned));
	vector<node>arm,nod,vec;
	for(int i=1;i<=m;++i){
		int u=a[i];
		for(int j=16;~j;--j)if(fa[j][u]>1&&dis[a[i]]<=dis[fa[j][u]]+k)u=fa[j][u];
		if(dis[a[i]]<=k)vec.pb(node(u,k-dis[a[i]]));
		else tag[u]=1;
	}
	for(int i=0;i<e[1].size();++i)if(dfs2(e[1][i].v,1))ned[e[1][i].v]=1;
	sort(vec.begin(),vec.end());
	for(int i=0;i<vec.size();++i){
		int u=vec[i].u;
		if(ned[u]&&vec[i].dis<dis[u])ned[u]=0;
		else arm.pb(vec[i]);
	}
	for(int i=0;i<e[1].size();++i)if(ned[e[1][i].v])nod.pb(node(e[1][i].v,e[1][i].w));
	sort(arm.begin(),arm.end()),sort(nod.begin(),nod.end());
	if(arm.size()<nod.size())return 0;
	int i=0,j=0;
	while(i<arm.size()&&j<nod.size())
		if(arm[i].dis>=nod[j].dis)++i,++j;
		else ++i;
	return j==nod.size();
}
signed main(){
	n=read();
	LL l=0,r=0;
	for(int i=1;i<n;++i){
		int x=read(),y=read(),z=read();
		e[x].pb(edge(y,z)),e[y].pb(edge(x,z)),r+=z;
	}
	dfs1(1,0);
	m=read();
	for(int i=1;i<=m;++i)a[i]=read();
	while(l<=r){
		LL mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",ans);
	return 0;
}
