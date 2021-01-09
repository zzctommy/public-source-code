//Orz cyn2006
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
int rdc(){
	char ch=getchar();
	while(ch!='='&&ch!='>'&&ch!='<')ch=getchar();
	if(ch=='>')return 1;
	else if(ch=='<')return -1;
	return 0;
}
#define N 2005
int n,m,a[N][N],fa[N],ind[N],val[N];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
int head[N],num_edge;
struct edge{int nxt,to;}e[N*N];
void addedge(int fr,int to){
	if(fr==to)puts("NO"),exit(0);
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
void topo(){
	queue<int>q;
	for(int i=1;i<=n+m;++i)if(!ind[find(i)]&&find(i)==i)q.push(i),val[i]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		// cerr<<u<<' '<<ind[u]<<'\n';
		if(ind[u]<0)puts("No"),exit(0);
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			val[v]=max(val[u]+1,val[v]);
			if(--ind[v]<=0)q.push(v);
		}
	}
	for(int i=1;i<=n+m;++i)if(ind[i])puts("No"),exit(0);
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			a[i][j]=rdc();
	for(int i=1;i<=n+m;++i)fa[i]=i;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(!a[i][j])fa[find(i)]=find(j+n);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(a[i][j]==-1)addedge(find(i),find(j+n)),++ind[find(j+n)];
			else if(a[i][j]==1)addedge(find(j+n),find(i)),++ind[find(i)];
	topo();
	puts("Yes");
	for(int i=1;i<=n;++i)printf("%d ",val[find(i)]);puts("");
	for(int i=1;i<=m;++i)printf("%d ",val[find(i+n)]);puts("");
	return 0;
}