#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define fi first
#define se second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 100005
int n,k,d1,d2,f[N],g[N],F[N],G[N],S,T,dep[N],fa[N];
struct edge{int nxt,to;}e[N<<1];
int head[N],num_edge;
vector<int>d;
unordered_map<int,bool>mp[N];
void addedge(int fr,int to){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
void getd1(int u,int ft,int&pos){
	fa[u]=ft,dep[u]=dep[ft]+1;
	if(dep[u]>dep[pos])pos=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==ft)continue;
		getd1(v,u,pos);
	}
}
void getd2(int u,int ft){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==ft)continue;
		getd2(v,u);int w=mp[u][v]?-1:1;
		d2=max(d2,f[u]+f[v]+w);
		f[u]=max(f[u],f[v]+w);
	}
}
signed main(){
	n=read(),k=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		addedge(x,y),addedge(y,x);
	}
	getd1(1,dep[1]=0,S=0),getd1(S,dep[S]=0,T=0),d1=dep[T]-1;
	if(k==1)return printf("%d\n",2*(n-1)-d1+1),0;
	int u=T;while(u)d.pb(u),u=fa[u];
	for(int i=0;i<d.size()-1;++i)mp[d[i]][d[i+1]]=mp[d[i+1]][d[i]]=1;
	memset(f,0,sizeof(f));
	getd2(1,0);
	printf("%d\n",2*(n-1)-d1+1-d2+1);
	return 0;
}