const int N=500010;
struct edge{int nxt,v;}e[N<<1];
int n,m,S;
int mi[20][N<<1],id[20][N<<1],lg[N<<1],dfn[N],pw2[30],timer;
int hed[N],et;
void adde(int u,int v){++et,e[et].nxt=hed[u],e[et].v=v,hed[u]=et;}
void dfs(int u,int dep){
	dfn[u]=++timer,mi[0][timer]=dep,id[0][timer]=u;
	for(int i=hed[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(dfn[v])continue;
		dfs(v,dep+1),++timer,mi[0][timer]=dep,id[0][timer]=u;
	}
}
void init_ST(){
	lg[0]=-1,pw2[0]=1;
	for(int i=1;i<=(n<<1);++i)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=21;++i)pw2[i]=pw2[i-1]<<1;
	for(int i=1;i<=lg[n<<1];++i)
		for(int j=1;j<=(n<<1)-pw2[i]+1;++j){
			int t=j+pw2[i-1];
			if(mi[i-1][j]<mi[i-1][t])mi[i][j]=mi[i-1][j],id[i][j]=id[i-1][j];
			else mi[i][j]=mi[i-1][t],id[i][j]=id[i-1][t];
		}
}
int ask(int x,int y){
	int l=dfn[x],r=dfn[y];
	if(l>r)l^=r^=l^=r;
	int k=lg[r-l+1],t=r-pw2[k]+1;
	if(mi[k][l]<mi[k][t])return id[k][l];
	else return id[k][t];
}