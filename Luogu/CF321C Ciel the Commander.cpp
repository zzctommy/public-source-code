#include<bits/stdc++.h>
int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=100005;
int n,rt,ans[N],siz[N],mx[N];
bool used[N];
struct edge{
	int nxt,to;
}e[N<<1];
int head[N],num_edge;
void addedge(int fr,int to){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
void getrt(int u,int ft,int totsize){
	siz[u]=1,mx[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(used[v]||v==ft)continue;
		getrt(v,u,totsize);
		siz[u]+=siz[v];
		mx[u]=std::max(mx[u],siz[v]);
	}
	mx[u]=std::max(mx[u],totsize-siz[u]);
	if(mx[u]<mx[rt])rt=u;
}
void solve(int u,int dep){
	ans[u]=dep,used[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(used[v])continue;
		rt=0,getrt(v,u,siz[v]);
		solve(rt,dep+1);
	}
}
signed main(){
	n=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		addedge(x,y),addedge(y,x);
	}
	mx[rt=0]=n,getrt(1,0,n),solve(rt,0);
	for(int i=1;i<=n;++i)printf("%c ",ans[i]+'A');
}