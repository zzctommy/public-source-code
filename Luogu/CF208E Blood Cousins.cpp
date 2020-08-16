#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100009;
const int M=18*N;
vector<int>g[N];
int n,fa[18][N],m,dep[N],ans[N];
int root[N],val[M],ls[M],rs[M],tot;
struct QUE {
	int id,x;
	QUE(){}
	QUE(int id_,int x_){id=id_,x=x_;}
};
vector<QUE>q[N];
int kth_fa(int x,int k) {
	int res=x;
	for(int i=0;i<17;++i)
		if(k>>i&1)res=fa[i][res];
	return res;
}
void change(int&p,int l,int r,int pos,int k) {
	if(!p)p=++tot;
	if(l==r){val[p]+=k;return;}
	int mid=(l+r)>>1;
	if(pos<=mid)change(ls[p],l,mid,pos,k);
	else change(rs[p],mid+1,r,pos,k);
}
int merge(int x,int y) {
	if(!x||!y)return x|y;
	val[x]+=val[y];
	ls[x]=merge(ls[x],ls[y]);
	rs[x]=merge(rs[x],rs[y]);
	return x;
}
int ask(int p,int l,int r,int pos) {
	if(l==r)return val[p];
	int mid=(l+r)>>1;
	if(pos<=mid)return ask(ls[p],l,mid,pos);
	else return ask(rs[p],mid+1,r,pos);
}
void dfs(int u) {
	for(int v:g[u])
		dep[v]=dep[u]+1,dfs(v),root[u]=merge(root[u],root[v]);
	if(u)change(root[u],1,n,dep[u],1);
	for(QUE i:q[u])ans[i.id]=ask(root[u],1,n,dep[i.x])-1;
}
signed main() {
	n=rd();
	for(int i=1;i<=n;++i)g[fa[0][i]=rd()].pb(i);
	for(int i=1;i<=17;++i)
		for(int j=1;j<=n;++j)
			fa[i][j]=fa[i-1][fa[i-1][j]];
	m=rd();
	for(int i=1;i<=m;++i){
		int x=rd(),k=rd(),p=kth_fa(x,k);
		if(p)q[p].pb(QUE(i,x));
	}
	dfs(0);
	for(int i=1;i<=m;++i)printf("%d\n",ans[i]);
	return 0;
}