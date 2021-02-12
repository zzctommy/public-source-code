#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int LIM=2000;
const int FYYAKKAKK=LIM+5;
const int N=(FYYAKKAKK+5)*2;
const int M=(60*FYYAKKAKK+2*FYYAKKAKK+FYYAKKAKK*sqrt(LIM))*2;
const int inf=0x3f3f3f3f;
int n,m,id[N];
int dep[N],ND,S,T,mf;
int hed[N],et=1,cur[N];
struct edge{int nx,to,fl;}e[M];
void addedge(int u,int v,int fl){e[++et].nx=hed[u],e[et].to=v,e[et].fl=fl,hed[u]=et;}
void adde(int u,int v,int fl){addedge(u,v,fl),addedge(v,u,0);}
vector<int>vc[55];
inline bool bfs(){
	queue<int>q;
	for(int i=1;i<=ND;++i)cur[i]=hed[i],dep[i]=0;
	q.push(S),dep[S]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=hed[u];i;i=e[i].nx){
			int v=e[i].to;
			if(e[i].fl&&!dep[v])
				dep[v]=dep[u]+1,q.push(v);
		}
	}
	return dep[T]>0;
}
int dfs(int u,int fl){
	if(u==T)return fl;
	int us=0,rl;
	for(int i=cur[u];i&&us<fl;i=e[i].nx){
		int v=e[i].to;cur[u]=i;
		if(e[i].fl&&dep[v]==dep[u]+1){
			rl=dfs(v,min(e[i].fl,fl-us));
			if(rl)e[i].fl-=rl,e[i^1].fl+=rl,us+=rl;
		}
	}
	return us;
}

signed main(){
	n=read();
	S=LIM*2+1,T=S+1,ND=T;
	for(int i=1,now=0;;++i){
		adde(S,i,1),adde(i+LIM,T,1);
		for(int j=1;j*j-i<i;++j)
			if(j*j-i>0)adde(j*j-i,i+LIM,1);
		while(bfs())mf+=dfs(S,inf);
		if(mf==i-now){
			for(int j=hed[i+LIM];j;j=e[j].nx){
				if(e[j].fl&&e[j].to<=i)id[i]=id[e[j].to],vc[id[e[j].to]].pb(i);
			}
		}else{
			++now;
			if(now>n){
				printf("%d\n",i-1);
				break;
			}
			vc[now].pb(i),id[i]=now;
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=0,up=sz(vc[i]);j<up;++j)printf("%d ",vc[i][j]);
		puts("");
	}
}