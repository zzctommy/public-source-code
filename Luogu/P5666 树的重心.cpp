#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return x*f;
}
const int N=300010;
int T;
int n;
LL ans;
int mx[N],root,siz[N];
int head[N],num_edge;
int A,B,in[N],f[N];
struct edge {
	int to,nxt;
}e[N<<1];
void addedge(int from,int to) {
	++num_edge;
	e[num_edge].nxt=head[from];
	e[num_edge].to=to;
	head[from]=num_edge;
}
struct BIT {
	int n;LL tr[N];
	void init(int x) {
		n=x+1;
		fill(tr+1,tr+n+1,0);
	}
	void add(int x,int d) {
		for(rint i=++x;i<=n;i+=i&-i)
			tr[i]+=d;
	}
	LL ask(int x) {
		int res=0;
		for(rint i=++x;i>0;i-=i&-i)
			res+=tr[i];
		return res;
	}
	LL ask(int l,int r) {
		return ask(r)-ask(l-1);
	}
}t[2];
void clear() {
	num_edge=0;
	fill(head+1,head+n+1,0);
	fill(in+1,in+n+1,0);
	t[0].init(n),t[1].init(n);
	mx[root=0]=n;
	A=B=0;
	ans=0;
}
void getroot(int u,int ft) {
	siz[u]=1,mx[u]=f[u]=0;
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft)continue;
		getroot(v,u);
		siz[u]+=siz[v];
		mx[u]=max(mx[u],siz[v]);
	} 
	f[u]=mx[u];
	mx[u]=max(mx[u],n-siz[u]);
	if(mx[u]<mx[root])root=u;
}
void solve(int u,int ft) {
	t[0].add(siz[ft],-1),t[0].add(n-siz[u],1);
	if(u!=root) {
		ans+=1ll*u*t[0].ask(n-(siz[u]<<1),n-(f[u]<<1));
		ans+=1ll*u*t[1].ask(n-(siz[u]<<1),n-(f[u]<<1));
		in[u]|=in[ft];
		if(siz[u]<=n-(siz[in[u]?B:A]<<1))ans+=root;
	}
	t[1].add(siz[u],1);
	for(rint i=head[u];i;i=e[i].nxt)
		if(e[i].to!=ft)solve(e[i].to,u);
	t[0].add(siz[ft],1),t[0].add(n-siz[u],-1);
	if(u!=root)
		ans-=1ll*u*t[1].ask(n-(siz[u]<<1),n-(f[u]<<1));
}
void Main() {
 	n=rd();
	clear();
	for(rint i=1;i<n;++i) {
		int x=rd(),y=rd();
		addedge(x,y),addedge(y,x);
	}
	getroot(1,0),getroot(root,0);
	for(rint i=head[root];i;i=e[i].nxt) {
		int v=e[i].to;
		if(siz[v]>=siz[A])B=A,A=v;
		else if(siz[v]>siz[B])B=v;
	}
	for(rint i=0;i<=n;++i)t[0].add(siz[i],1);
	in[A]=1,solve(root,0);
	printf("%lld\n",ans);
}
signed main() {
	for(T=rd();T;--T)Main();
	return 0;
}
