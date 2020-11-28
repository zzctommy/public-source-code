#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
template<class T>inline bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>inline bool ckmin(T&x,T y){return x>y?x=y,1:0;}

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
LL dfs(int u,int fl){
	if(u==T)return fl;
	int rl=0,used=0;
	for(int i=cur[u];i;i=e[i].nx){
		int v=e[i].to;cur[u]=i;
		if(e[i].fl&&dis[v]==dis[u]+1){
			rl=dfs(v,min(e[i].fl,fl-used));
			if(rl)e[i].fl-=rl,e[i^1].fl+=rl,used+=rl;
		}
	}
	return used;
}
LL maxflow(){
	LL res=0;
	while(bfs(S,T))res+=dfs(S,inf);
	return res;
}

};

const int N=22;
const int inf=0x3f3f3f3f;
Dinic<800,400*70>mf;
int r,c,d,h[N][N],cnt;
int id(int x,int y){return (x-1)*c+y;}
signed main(){
	r=read(),c=read(),d=read();
	mf.S=r*c*2+1,mf.T=mf.S+1;
	for(int i=1;i<=r;++i){
		for(int j=1;j<=c;++j){
			char ch=getchar();
			while(!isdigit(ch))ch=getchar();
			h[i][j]=ch-'0';
		}
	}
	for(int i=1;i<=r;++i)
		for(int j=1;j<=c;++j)
			if(h[i][j]){
				mf.adde(id(i,j),id(i,j)+r*c,h[i][j]);
				for(int k=max(1,i-d);k<=min(r,i+d);++k)
					for(int l=max(1,j-d);l<=min(c,j+d);++l){
						if(i==k&&j==l)continue;
						if(h[k][l]&&(k-i)*(k-i)+(l-j)*(l-j)<=d*d)mf.adde(id(i,j)+r*c,id(k,l),inf);
					}
				if(i<=d||j<=d||r-i<d||c-j<d)mf.adde(id(i,j)+r*c,mf.T,inf);
			}
	for(int i=1;i<=r;++i)
		for(int j=1;j<=c;++j){
			char ch=getchar();
			while(ch!='L'&&ch!='.')ch=getchar();
			if(ch=='L')mf.adde(mf.S,id(i,j),1),++cnt;
		}
	printf("%lld\n",cnt-mf.maxflow());
	return 0;
}
/*
5 8 2
00000000
02000000
00321100
02000000
00000000
........
........
..LLLL..
........
........

*/