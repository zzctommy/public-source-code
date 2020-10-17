#include<bits/stdc++.h>
using namespace std;
const int N=200005;
const int K=1000006;
int max(int x,int y){return x>y?x:y;}
int min(int x,int y){return x<y?x:y;}
int n,k,ans,cnt[K];
struct egde{
	int nxt,to,val;
}e[N<<1];
int head[N],num_edge;
inline void add(int from,int to,int val)
{
	++num_edge;
	e[num_edge].to=to;
	e[num_edge].nxt=head[from];
	e[num_edge].val=val;
	head[from]=num_edge;
}
int rt,sum,mx[N],size[N],dist[N];
bool used[N];
void getrt(int u,int fa)
{
	mx[u]=0,size[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa||used[v])continue;
		getrt(v,u);
		size[u]+=size[v];
		mx[u]=max(mx[u],size[v]);
	}	
	mx[u]=max(sum-mx[u],mx[u]);
	if(mx[u]<mx[rt])rt=u;
}
void getdis(int u,int fa,int dep)
{
	if(dist[u]>=0&&dist[u]<=k)ans=min(ans,dep+cnt[k-dist[u]]);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(used[v]||v==fa)continue;
		dist[v]=dist[u]+e[i].val;
		getdis(v,u,dep+1);
	}
}
void upd(int u,int fa,int dep,int o)
{
	if(dist[u]>=0&&dist[u]<=k)
	{
		if(o)cnt[dist[u]]=min(cnt[dist[u]],dep);
		else cnt[dist[u]]=n;
	}
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa||used[v])continue;
		upd(v,u,dep+1,o);
	}
}
void calc(int u)
{
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(used[v])continue;
		dist[v]=e[i].val;
		getdis(v,u,1);
		upd(v,u,1,1);
	}
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(used[v])continue;
		upd(v,u,1,0);
	}
}
void solve(int u)
{
	used[u]=true;calc(u);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(used[v])continue;
		rt=0;
		sum=size[v];
		getrt(v,u);
		solve(rt);
	}
}
int main()
{
	scanf("%d%d",&n,&k);ans=n;
	for(int i=1,x,y,z;i<n;++i)
		scanf("%d%d%d",&x,&y,&z),++x,++y,add(x,y,z),add(y,x,z);
	for(int i=1;i<=k;++i)cnt[i]=n;
	sum=n,mx[rt=0]=n,getrt(1,0),solve(rt);
	ans=ans==n?-1:ans;
	printf("%d\n",ans);
	return 0;
}