#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define x first
#define y second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 70005
#define M 1500005
int n,m;
int to[N],cmp_D,rt;
int dis[N<<1];
bool vis[N<<1];
int nxt[M],head[N],cnt,ver[M];
int z[N];
int L[M],R[M],D[M],U[M],W[M];
struct kdt{
	int mx[2],mn[2],ch[2],d[2],id;
	#define ls(x) t[x].ch[0]
	#define rs(x) t[x].ch[1]
}t[N];
struct dij{
	int u,dis;
	dij(){u=dis=0;}
	dij(int u_,int d_){u=u_,dis=d_;}
	inline bool operator < (const dij&t)const{return dis>t.dis;}
};
bool cmp(const kdt&a,const kdt&b){return a.d[cmp_D]<b.d[cmp_D];}
void pushup(int p){
	t[p].mx[0]=t[p].mn[0]=t[p].d[0];
	t[p].mx[1]=t[p].mn[1]=t[p].d[1];
	if(ls(p))
		t[p].mx[0]=max(t[p].mx[0],t[ls(p)].mx[0]),
		t[p].mx[1]=max(t[p].mx[1],t[ls(p)].mx[1]),
		t[p].mn[0]=min(t[p].mn[0],t[ls(p)].mn[0]),
		t[p].mn[1]=min(t[p].mn[1],t[ls(p)].mn[1]);
	if(rs(p))
		t[p].mx[0]=max(t[p].mx[0],t[rs(p)].mx[0]),
		t[p].mx[1]=max(t[p].mx[1],t[rs(p)].mx[1]),
		t[p].mn[0]=min(t[p].mn[0],t[rs(p)].mn[0]),
		t[p].mn[1]=min(t[p].mn[1],t[rs(p)].mn[1]);
}
int build(int l,int r,int D){
	int mid=(l+r)>>1;
	cmp_D=D,nth_element(t+l,t+mid,t+r+1,cmp),to[t[mid].id]=mid;
	if(l!=mid)ls(mid)=build(l,mid-1,D^1);
	if(r!=mid)rs(mid)=build(mid+1,r,D^1);
	return pushup(mid),mid;
}
void get(int p,int l,int r,int d,int u,int lim){
	if(!p||dis[p]<=lim)return;
	if(l<=t[p].mn[0]&&t[p].mx[0]<=r&&d<=t[p].mn[1]&&t[p].mx[1]<=u)return z[++z[0]]=p,void();
	if(r<t[p].mn[0]||l>t[p].mx[0]||u<t[p].mn[1]||d>t[p].mx[1])return;
	if(l<=t[p].d[0]&&t[p].d[0]<=r&&d<=t[p].d[1]&&t[p].d[1]<=u)z[++z[0]]=p+n;
	get(ls(p),l,r,d,u,lim),get(rs(p),l,r,d,u,lim);
}
void Dij(){
	priority_queue<dij>q;
	memset(dis,0x3f,sizeof(dis));
	q.push(dij(to[1]+n,dis[to[1]+n]=0));
	while(!q.empty()){
		dij now=q.top();q.pop();
		int u=now.u;
		if(vis[u])continue;
		vis[u]=1;
		if(u<=n){
			if(ls(u)&&dis[ls(u)]>dis[u])dis[ls(u)]=dis[u],q.push(dij(ls(u),dis[ls(u)]));
			if(rs(u)&&dis[rs(u)]>dis[u])dis[rs(u)]=dis[u],q.push(dij(rs(u),dis[rs(u)]));
			if(dis[u+n]>dis[u])dis[u+n]=dis[u],q.push(dij(u+n,dis[u+n]));
		}else{
			for(int i=head[u-n];i;i=nxt[i]){
				int t=ver[i],V=dis[u]+W[t];
				z[0]=0,get(rt,L[t],R[t],D[t],U[t],V);
				for(int j=1;j<=z[0];++j)
					if(dis[z[j]]>V)dis[z[j]]=V,q.push(dij(z[j],dis[z[j]]));
			}
		}
	}
}
signed main(){
	n=read(),m=read(),read(),read();
	for(int i=1;i<=n;++i)t[i].d[0]=read(),t[i].d[1]=read(),t[i].id=i;
	rt=build(1,n,0);
	for(int i=1;i<=m;++i){
		int x=read();
		ver[++cnt]=i,nxt[cnt]=head[to[x]],head[to[x]]=cnt;
		W[i]=read(),L[i]=read(),R[i]=read(),D[i]=read(),U[i]=read();
	}
		
	Dij();
	for(int i=2;i<=n;++i)printf("%d\n",dis[to[i]+n]);
	return 0;
}