#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100005;
const int M=320;
int n,m,c[N],S,lsh[N],len;
int head[N],num_edge;
int ld[N],rd[N],timer,rev[N];
int bin[N],ans[N],sum[M],a[N],L[N],R[N],bel[N],num;
struct edge{
	int nxt,to;
}e[N<<1];
struct ASK {
	int id,l,r,k;
	inline bool operator < (const ASK&rhs)const{return bel[l]!=bel[rhs.l]?l<rhs.l:bel[l]&1?r<rhs.r:r>rhs.r;}
}q[N];
void addedge(int fr,int to){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge; 
}
void dfs(int u,int ft){
	ld[u]=++timer,rev[timer]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==ft)continue;
		dfs(v,u);
	}
	rd[u]=timer;
}
void upd(int x,int d){
	a[x]+=d,sum[bel[x]]+=d;
}
int ask(int l,int r){
	if(l>r)return 0;
	int res=0;
	if(bel[l]==bel[r]){
		for(int i=l;i<=r;++i)res+=a[i];
		return res;
	}
	for(int i=l;i<=R[bel[l]];++i)res+=a[i];
	for(int i=L[bel[r]];i<=r;++i)res+=a[i];
	for(int i=bel[l]+1;i<bel[r];++i)res+=sum[i];
	return res;
}
void add(int x){upd(bin[x],-1),++bin[x],upd(bin[x],1);}
void pop(int x){upd(bin[x],-1),--bin[x],upd(bin[x],1);}
signed main() {
	n=read(),m=read(),S=sqrt(n)+1,num=(n-1)/S+1;
	for(int i=1;i<=n;++i)c[i]=lsh[i]=read();
	sort(lsh+1,lsh+n+1),len=unique(lsh+1,lsh+n+1)-lsh-1;
	for(int i=1;i<=n;++i)c[i]=lower_bound(lsh+1,lsh+len+1,c[i])-lsh;
	for(int i=1;i<=num;++i)L[i]=R[i-1]+1,R[i]=i*S;
	R[num]=n;
	for(int i=1;i<=num;++i)
		for(int j=L[i];j<=R[i];++j)
			bel[j]=i;
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		addedge(x,y),addedge(y,x);
	}
	dfs(1,0);
	for(int i=1;i<=m;++i) {
		int u=read(),k=read();
		q[i].l=ld[u],q[i].r=rd[u],q[i].k=k,q[i].id=i;
	}
	sort(q+1,q+m+1);
	for(int i=1,l=1,r=0;i<=m;++i) {
		while(l>q[i].l)add(c[rev[--l]]);
		while(r<q[i].r)add(c[rev[++r]]);
		while(l<q[i].l)pop(c[rev[l++]]);
		while(r>q[i].r)pop(c[rev[r--]]);
		ans[q[i].id]=ask(q[i].k,n);
	}
	for(int i=1;i<=m;++i)printf("%d\n",ans[i]);
	return 0;
}
