include<bits/stdc++.h>
using namespace std;
const int N=10005;
const int M=100005;
const int inf=(1<<30);
int n,m,s,t,num_edge=1,maxflow;
int head[N],cur[N],dep[N],gap[N];
struct egde{
	int to,next,val;
}e[M<<1];
void add(int from,int to,int len)
{
	++num_edge;
	e[num_edge].to=to;
	e[num_edge].val=len;
	e[num_edge].next=head[from];
	head[from]=num_edge;
}
void bfs(int st)
{
	memset(dep,-1,sizeof(dep));
	queue<int>q;
	q.push(st);
	dep[st]=0;
	gap[0]=1;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(dep[v]!=-1)continue;
			q.push(v);
			dep[v]=dep[u]+1;
			gap[dep[v]]++;
		}
	}
}
int dfs(int u,int flow)
{
	if(u==t)
	{
		maxflow+=flow;
		return flow;
	}
	int used=0,rlow=0;
	for(int i=cur[u];i;i=e[i].next)
	{
		int v=e[i].to;
		cur[u]=i;
		if(e[i].val&&dep[v]+1==dep[u])
		{
			rlow=dfs(v,min(flow-used,e[i].val));
			if(rlow)
			{
				used+=rlow;
				e[i].val-=rlow;
				e[i^1].val+=rlow;
			}
		}
		if(used==flow)return used;
	}
	--gap[dep[u]];
	if(!gap[dep[u]])dep[s]=n+1;
	++dep[u];
	++gap[dep[u]];
	return used;
}
int isap()
{
	bfs(t);
	while(dep[s]<n)
	{
		memcpy(cur,head,sizeof(head));
		dfs(s,inf);
	}
	return maxflow;
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		add(v,u,0);
	}
	printf("%d\n",isap());
	return 0;
}