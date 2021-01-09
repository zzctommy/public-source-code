template<int NN,int MM>
struct Dinic{

static const int N=NN+5;
static const int M=(MM<<1)+5;
static const int inf=1<<30;

int hed[N],et,S,T;
struct edge{int fl,nx,to;}e[M];
int dis[N],cur[N];
Dinic(){et=1,memset(hed,0,sizeof(hed));}
void clear(){Dinic();}
void addedge(int u,int v,int fl){e[++et].nx=hed[u],hed[u]=et,e[et].fl=fl,e[et].to=v;}
void adde(int u,int v,int fl){addedge(u,v,fl),addedge(v,u,0);}

bool bfs(int s,int t){
	queue<int>q;
	for(int i=1;i<=N;++i)dis[i]=0,cur[i]=hed[i];
	q.push(s),dis[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=hed[u];i;i=e[i].nx){
			int v=e[i].to;
			if(e[i].fl&&!dis[v]){
				dis[v]=dis[u]+1,q.push(v);
				if(v==t)return 1;
			}
		}
	}
	return 0;
}
int dfs(int u,int fl){
	if(u==T)return fl;
	int rl=0,used=0;
	for(int i=cur[u];i;i=e[i].nx){
		int v=e[i].to;cur[u]=i;
		if(e[i].fl&&dis[v]==dis[u]+1){
			rl=dfs(v,min(e[i].fl,fl-used));
			if(rl){
				e[i].fl-=rl,e[i^1].fl+=rl,used+=rl;
				if(used==fl)break;
			}
		}
	}
	return used;
}
int maxflow(){
	int res=0;
	while(bfs(S,T))res+=dfs(S,inf);
	return res;
}

};