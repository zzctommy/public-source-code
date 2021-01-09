#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100005;
const int M=1000005;
const int K=N<<1;
const int T=K*23;
int n,m,q,h[K],F[K],cnt,fa[20][K],cpy[N],len,w[K];
int head[K],num_edge;
int ld[K],rd[K],rev[K],timer,sum[K];
int val[T],ls[T],rs[T],tot,root[K];
int find(int x){return x==F[x]?x:F[x]=find(F[x]);}
struct node{
	int u,v,d;
	inline bool operator < (const node&rhs)const{return d<rhs.d;}
}a[M];
struct edge{
	int nxt,to;
}e[N<<1];
void addedge(int fr,int to){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
void dfs(int u){
	ld[u]=++timer,rev[timer]=u;
	if(u<=n)++sum[u];
	for(int i=head[u];i;i=e[i].nxt)dfs(e[i].to),sum[u]+=sum[e[i].to];
	rd[u]=timer;
}
void update(int &p,int pre,int l,int r,int v){
	p=++tot;
	ls[p]=ls[pre],rs[p]=rs[pre],val[p]=val[pre]+1;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(v<=mid)update(ls[p],ls[pre],l,mid,v);
	else update(rs[p],rs[pre],mid+1,r,v);
}
int query(int p,int pre,int l,int r,int k){
	if(l==r)return l;
	int x=val[rs[p]]-val[rs[pre]],mid=(l+r)>>1;
	if(k<=x)return query(rs[p],rs[pre],mid+1,r,k);
	else return query(ls[p],ls[pre],l,mid,k-x);
}
signed main(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=n;++i)cpy[++len]=h[i]=read();
	for(int i=1;i<n<<1;++i)F[i]=i;
	sort(cpy+1,cpy+len+1),len=unique(cpy+1,cpy+len+1)-cpy-1;
	for(int i=1;i<=n;++i)h[i]=lower_bound(cpy+1,cpy+len+1,h[i])-cpy;
	for(int i=1;i<=m;++i)a[i].u=read(),a[i].v=read(),a[i].d=read();
	sort(a+1,a+m+1),cnt=n;
	for(int i=1;i<=m;++i){
		int u=a[i].u,v=a[i].v;
		int fx=find(u),fy=find(v);
		if(fx!=fy){
			++cnt,w[cnt]=a[i].d;
			addedge(cnt,fx),addedge(cnt,fy);
			fa[0][fx]=fa[0][fy]=F[fx]=F[fy]=cnt;
			if(cnt==2*n-1)break;
		}
	}
	dfs(cnt);
	for(int i=1;i<20;++i)
		for(int j=1;j<=cnt;++j)
			fa[i][j]=fa[i-1][fa[i-1][j]];
	for(int i=1;i<=cnt;++i)
		if(rev[i]<=n)update(root[i],root[i-1],1,len,h[rev[i]]);
		else root[i]=root[i-1];
	while(q--){
		int x=read(),y=read(),z=read();
		for(int i=19;~i;--i) {
			if(fa[i][x]&&w[fa[i][x]]<=y)x=fa[i][x];
		}
		if(z>sum[x])puts("-1");
		else printf("%d\n",cpy[query(root[rd[x]],root[ld[x]-1],1,len,z)]);
	}
	return 0;
}
