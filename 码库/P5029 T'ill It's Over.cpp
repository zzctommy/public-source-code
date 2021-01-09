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
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}

const int K=100005;
const int N=11*K;
const int M=N<<1;
const int inf=0x3f3f3f3f;

int n,m,k,tot,rt[2],ls[K<<2],rs[K<<2];
int hed[N],et=1,S,T,cur[N],dis[N],mf;
struct edge{int nx,to,fl;}e[M];
void addedge(int u,int v,int fl){e[++et].nx=hed[u],e[et].to=v,e[et].fl=fl,hed[u]=et;}
void adde(int u,int v,int fl){addedge(u,v,fl),addedge(v,u,0);}
bool bfs(int s,int t){
	queue<int>q;
	rep(i,1,tot)dis[i]=0,cur[i]=hed[i];
	dis[s]=1,q.push(s);
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
void build(int&x,int&y,int l=1,int r=k){
	x=++tot,y=l==r?x:++tot;
	if(l==r){
		if(l==1)adde(S,x,n);
		if(l==k)adde(y,T,n);
		return;
	}
	int mid=(l+r)>>1;
	build(ls[x],ls[y],l,mid);
	build(rs[x],rs[y],mid+1,r);
	adde(x,ls[x],inf),adde(x,rs[x],inf);
	adde(ls[y],y,inf),adde(rs[y],y,inf);
}
void link(int p,int ql,int qr,int pos,int op,int l=1,int r=k){
	if(ql<=l&&r<=qr){
		if(!op)adde(pos,p,inf);
		else adde(p,pos,inf);
		return;
	}
	int mid=(l+r)>>1;
	if(ql<=mid)link(ls[p],ql,qr,pos,op,l,mid);
	if(mid<qr)link(rs[p],ql,qr,pos,op,mid+1,r);
}
signed main(){
	n=read(),m=read(),k=read(),S=++tot,T=++tot;
	build(rt[0],rt[1]);
	rep(i,1,m){
		int op=read(),l=read(),a1,b1,a2,b2;
		if(op==1)a1=read(),a2=a1,b1=read(),b2=b1;
		else if(op==2)a1=read(),a2=read(),b1=read(),b2=b1;
		else if(op==3)a1=read(),a2=a1,b1=read(),b2=read();
		else a1=read(),a2=read(),b1=read(),b2=read();

		link(rt[0],b1,b2,tot+2,0);
		link(rt[1],a1,a2,tot+1,1);
		adde(tot+1,tot+2,l),tot+=2;
	}
	while(bfs(S,T))mf+=dfs(S,inf);
	printf("%d\n",mf);
}
/*
5 4 5
1 3 1 3
1 3 3 2
1 3 2 5
4 1 1 1 4 5

*/