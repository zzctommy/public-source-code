#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=200005;
const int M=400005;
int n,m,q,root[M],to[M];
struct node{
	int x,y,z;
}a[M];
struct Kruskal_Tree{//TYPE=0:max;TYPE=1:min
	int TYPE=-1,F[M],cnt,val[M],num_edge,head[M],fa[20][M],dep[M],ld[M],rd[M],timer,rev[M];
	Kruskal_Tree(){}
	void init(int t){TYPE=t;}
	int find(int x){return x==F[x]?x:F[x]=find(F[x]);}
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
		for(int i=1;1<<i<=dep[u];++i)fa[i][u]=fa[i-1][fa[i-1][u]];
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			dep[v]=dep[u]+1,fa[0][v]=u,dfs(v);
		}
		rd[u]=timer;
	}
	void build(){
		for(int i=1;i<n<<1;++i)F[i]=i;cnt=n;
		for(int i=1;i<=m;++i)a[i].z=TYPE?max(a[i].x,a[i].y):min(a[i].x,a[i].y);
		sort(a+1,a+m+1,[&](const node&a,const node&b){return TYPE?a.z<b.z:a.z>b.z;});
		for(int i=1;i<=m;++i){
			int u=a[i].x,v=a[i].y,fx=find(u),fy=find(v);
			if(fx!=fy){
				++cnt,val[cnt]=a[i].z;
				F[fx]=F[fy]=cnt;
				addedge(cnt,fx),addedge(cnt,fy);
				if(cnt==n*2-1)break;
			}
		}
		dfs(cnt);
	}
}T[2];
namespace seg{
	const int T=M*24;
	int ls[T],rs[T],val[T],tot;
	void update(int &p,int pre,int l,int r,int pos){
		p=++tot;
		ls[p]=ls[pre],rs[p]=rs[pre],val[p]=val[pre]+1;
		if(l==r)return;
		int mid=(l+r)>>1;
		if(pos<=mid)update(ls[p],ls[pre],l,mid,pos);
		else update(rs[p],rs[pre],mid+1,r,pos);
	}
	int query(int p,int pre,int ql,int qr,int l,int r){
		if(ql<=l&&r<=qr)return val[p]-val[pre];
		int mid=(l+r)>>1,res=0;
		if(ql<=mid)res+=query(ls[p],ls[pre],ql,qr,l,mid);
		if(mid<qr)res+=query(rs[p],rs[pre],ql,qr,mid+1,r);
		return res;
	}
}
signed main(){
	n=read(),m=read(),q=read(),T[0].init(0),T[1].init(1);
	for(int i=1;i<=m;++i)a[i].x=read()+1,a[i].y=read()+1;
	T[0].build(),T[1].build();
	for(int i=1;i<=n;++i)to[T[0].ld[i]]=T[1].ld[i];
	for(int i=1;i<n<<1;++i)
		if(T[0].rev[i]>n)root[i]=root[i-1];
		else seg::update(root[i],root[i-1],1,(n<<1)-1,to[i]);
	while(q--){
		int s=read()+1,e=read()+1,l=read()+1,r=read()+1;
		for(int i=19;~i;--i)if(T[0].fa[i][s]&&T[0].val[T[0].fa[i][s]]>=l)s=T[0].fa[i][s];
		for(int i=19;~i;--i)if(T[1].fa[i][e]&&T[1].val[T[1].fa[i][e]]<=r)e=T[1].fa[i][e];
		puts(seg::query(root[T[0].rd[s]],root[T[0].ld[s]-1],T[1].ld[e],T[1].rd[e],1,(n<<1)-1)?"1":"0");
	}
	return 0;
} 
