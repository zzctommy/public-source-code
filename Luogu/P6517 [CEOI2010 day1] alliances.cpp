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
#define per(i,y,x) for(int i=y,i##end=x;i>=i##end;--i)
#define broken cerr<<"lqx AK:"<<__LINE__<<' '<<__FUNCTION__<<endl
#define outedge cerr<<u<<' '<<v<<' '<<fl<<'\n'
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}

const int K=75;
const int N=K*K*3;
const int M=8*K*K*2;
const int inf=0x3f3f3f3f;

int n,m,a[K][K],tot,id[K][K][2],num[2];
char ans[K*3][K*3];
int dx[4]={0,0,-1,1},dy[4]={1,-1,0,0};
map<int,pair<int,int> >rev;
int dis[N],cur[N],mf,S,T,hed[N],et=1;
struct edge{int nx,to,fl;}e[M];
void addedge(int u,int v,int fl){e[++et].to=v,e[et].nx=hed[u],e[et].fl=fl,hed[u]=et;}
void adde(int u,int v,int fl){
	if(!u||!v)return;
	addedge(u,v,fl),addedge(v,u,0);
}
bool bfs(int s,int t){
	queue<int>q;
	rep(i,1,tot)cur[i]=hed[i],dis[i]=0;
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
	int rl,used=0;
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
signed main(){
	n=read(),m=read(),S=++tot,T=++tot;
	rep(i,1,n)rep(j,1,m){
		a[i][j]=read();
		num[(i+j)&1]+=a[i][j];
		if(!a[i][j])continue;
		if(a[i][j]==2)rev[id[i][j][0]=++tot]=mkp(i,j),rev[id[i][j][1]=++tot]=mkp(i,j);
		else rev[id[i][j][0]=++tot]=mkp(i,j);
	}
	if(num[0]!=num[1])return puts("Impossible!"),0;
	rep(i,1,n)rep(j,1,m){
		if(!a[i][j])continue;
		if((i+j)&1){
			if(a[i][j]==2)adde(S,id[i][j][0],1),adde(S,id[i][j][1],1);
			else adde(S,id[i][j][0],a[i][j]);
		}else {
			if(a[i][j]==2)adde(id[i][j][0],T,1),adde(id[i][j][1],T,1);
			else adde(id[i][j][0],T,a[i][j]);
			continue;
		}
		if(a[i][j]!=2){
			if(a[i+1][j]==2)adde(id[i][j][0],id[i+1][j][1],1);
			else adde(id[i][j][0],id[i+1][j][0],1);
			if(a[i-1][j]==2)adde(id[i][j][0],id[i-1][j][1],1);
			else adde(id[i][j][0],id[i-1][j][0],1);
			if(a[i][j+1]==2)adde(id[i][j][0],id[i][j+1][0],1);
			else adde(id[i][j][0],id[i][j+1][0],1);
			if(a[i][j-1]==2)adde(id[i][j][0],id[i][j-1][0],1);
			else adde(id[i][j][0],id[i][j-1][0],1);
		}else{
			if(a[i+1][j]==2)adde(id[i][j][1],id[i+1][j][1],1);
			else adde(id[i][j][1],id[i+1][j][0],1);
			if(a[i-1][j]==2)adde(id[i][j][1],id[i-1][j][1],1);
			else adde(id[i][j][1],id[i-1][j][0],1);
			if(a[i][j+1]==2)adde(id[i][j][0],id[i][j+1][0],1);
			else adde(id[i][j][0],id[i][j+1][0],1);
			if(a[i][j-1]==2)adde(id[i][j][0],id[i][j-1][0],1);
			else adde(id[i][j][0],id[i][j-1][0],1);
		}
	}
	while(bfs(S,T))mf+=dfs(S,inf);
	// cerr<<"flow:"<<mf<<' '<<num<<'\n';
	if(mf!=num[0])return puts("Impossible!"),0;

	rep(i,1,n)rep(j,1,m)if(a[i][j])ans[i*3-1][j*3-1]='O';
	rep(i,1,n*3)rep(j,1,m*3)if(!ans[i][j])ans[i][j]='.';
	for(int i=2;i<=et;i+=2){
		if(e[i^1].fl&&e[i].to!=S&&e[i].to!=T&&e[i^1].to!=S&&e[i^1].to!=T){
			pair<int,int>ed=rev[e[i].to],fr=rev[e[i^1].to];
			// cerr<<fr.fi<<' '<<fr.se<<' '<<ed.fi<<' '<<ed.se<<'\n';
			rep(j,0,3)if(mkp(fr.fi+dx[j],fr.se+dy[j])==ed){
				fr.fi=fr.fi*3-1,fr.se=fr.se*3-1;
				ed.fi=ed.fi*3-1,ed.se=ed.se*3-1;
				ans[fr.fi+dx[j]][fr.se+dy[j]]='X';
				ans[ed.fi-dx[j]][ed.se-dy[j]]='X';
			}
		}
	}
	rep(i,1,n*3){
		rep(j,1,m*3)putchar(ans[i][j]);
		puts("");
	}
	return 0;
}
/*
3 4
2 3 2 0
3 4 3 0
2 3 3 1

P6517_8.in
P6517_43.in
*/