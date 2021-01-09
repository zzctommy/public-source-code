const int N=405;
const int M=2*(N*2+N*N);
const int inf=0x3f3f3f3f;
const LL LLinf=0x3f3f3f3f3f3f3f3f;
int n,m,a[N],b[N],c[N][N],S,T,mf,tot;
struct node{int x,y,v;}d[N*N];
inline bool cmp(const node&a,const node&b){return a.v<b.v;}
LL mc,dis[N];
int hed[N],et=1,cur[N];
bool vis[N],inq[N];
struct edge{int nx,to,fl,w;}e[M];
void addedge(int u,int v,int fl,int w){e[++et].nx=hed[u],e[et].to=v,e[et].fl=fl,e[et].w=w,hed[u]=et;}
void adde(int u,int v,int fl,int w){addedge(u,v,fl,w),addedge(v,u,0,-w);}
bool bfs(){
    rep(i,1,T)dis[i]=LLinf,cur[i]=hed[i],inq[i]=0;
    queue<int>q;q.push(S),dis[S]=0;
    while(!q.empty()){
        int u=q.front();q.pop(),inq[u]=0;
        for(int i=hed[u];i;i=e[i].nx){
            int v=e[i].to;
            if(e[i].fl&&ckmin(dis[v],dis[u]+e[i].w)){
                if(!inq[v])q.push(v),inq[v]=1;
            }
        }
    }
    return dis[T]<LLinf;
}
int dfs(int u,int fl){
    vis[u]=1;
    if(u==T)return fl;
    int used=0,rl=0;
    for(int i=cur[u];i;i=e[i].nx){
        int v=e[i].to;cur[u]=i;
        if((!vis[v]||v==T)&&e[i].fl&&dis[v]==dis[u]+e[i].w){
            rl=dfs(v,min(e[i].fl,fl-used));
            if(rl)e[i].fl-=rl,e[i^1].fl+=rl,mc+=1ll*e[i].w*rl,used+=rl;
            if(used==fl)break;
        }
    }
    return used;
}
void mcmf(){
	while(bfs()){
        vis[T]=1;
        while(vis[T])fill(vis,vis+T+1,0),mf+=dfs(S,inf);
    }
}