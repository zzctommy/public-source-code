#include<bits/stdc++.h>
using namespace std;
const int N=10500;
const int M=400500;
const int inf=(1<<30);
int n,m,s,t,num_edge=1;
int head[N],h[N],o[N],cnth[N];
bool inq[N];
struct edge{
	int to,next,val;
}e[M];
void add(int from,int to,int len)
{
	++num_edge;
	e[num_edge].val=len;
	e[num_edge].to=to;
	e[num_edge].next=head[from];
	head[from]=num_edge;
}
void bfs()
{
	memset(h,0x3f,sizeof(h));
	inq[t]=true;
	h[t]=0;
	queue<int>q;
	q.push(t);
	while(!q.empty())
	{
		int cur=q.front();q.pop();
		inq[cur]=false;
		for(int i=head[cur];i;i=e[i].next)
		{
			int to=e[i].to;
			if(e[i^1].val&&h[to]>h[cur]+1)
			{
				h[to]=h[cur]+1;
				if(!inq[to])
				{
					inq[to]=true;
					q.push(to);
				}
			}
		}
	}
}
struct cmp{
	inline bool operator () (int a,int b)const {
		return h[a]<h[b];
	}
};
priority_queue<int,vector<int>,cmp>q;
inline void push(int now)
{
	for(int i=head[now];i;i=e[i].next)
	{
		int to=e[i].to;
		if(e[i].val&&h[to]+1==h[now])
		{
			int mi=min(e[i].val,o[now]);
			e[i].val-=mi;
			e[i^1].val+=mi;
			o[now]-=mi;
			o[to]+=mi;
			if(!inq[to]&&to!=s&&to!=t)
			{
				inq[to]=true;
				q.push(to);
			}
			if(!o[now])break;
		}
	}
}
inline void relable(int now)
{
	h[now]=inf;
	for(int i=head[now];i;i=e[i].next)
	{
		int to=e[i].to;
		if(h[to]+1<h[now]&&e[i].val)h[now]=h[to]+1;
	}
}
int hlpp()
{
	bfs();
	if(h[s]==0x3f3f3f3f)return 0;
	h[s]=n;
	for(int i=1;i<=n;i++)if(h[i]<0x3f3f3f3f)cnth[h[i]]++;
	for(int i=head[s];i;i=e[i].next)
	{
		int to=e[i].to;
		if(e[i].val)
		{
			o[s]-=e[i].val;
			o[to]+=e[i].val;
			e[i^1].val=e[i].val;
			e[i].val=0;
			if(!inq[to]&&to!=s&&to!=t)
			{
				inq[to]=true;
				q.push(to);
			}
		}
	}
	while(!q.empty())
	{
		int cur=q.top();q.pop();
		inq[cur]=false;
		push(cur);
		if(o[cur])
		{
			--cnth[h[cur]];
			if(!cnth[h[cur]])
			{
				for(int i=1;i<=n;i++)
				{
					if(i!=s&&i!=t&&h[i]>h[cur]&&h[i]<n+1)
					{
						h[i]=n+1;
					}
				}
			}
			relable(cur);
			cnth[h[cur]]++;
			q.push(cur);
			inq[cur]=true;
		}
	}
	return o[t];
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
	printf("%d\n",hlpp());
	return 0;
}