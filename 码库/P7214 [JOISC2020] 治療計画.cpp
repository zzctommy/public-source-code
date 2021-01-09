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
const int N=100005;
int n,m;
LL dis[N];
bool vis[N];
struct node{int T,L,R,C;}a[N];
inline bool cmp(const node&a,const node&b){return a.T<b.T;}
priority_queue<pair<LL,int> >pq;
struct SegmentTree{
static const int T=N<<2;
#define lc (p<<1)
#define rc (p<<1|1)
set<pair<int,int> >S[T];
void change(int pos,int val,int l=1,int r=m,int p=1){
	S[p].insert(mkp(val,pos));
	if(l==r)return;
	int mid=(l+r)>>1;
	if(pos<=mid)change(pos,val,l,mid,lc);
	else change(pos,val,mid+1,r,rc);
}
void link(int ql,int qr,int val,LL d,int l=1,int r=m,int p=1){
	if(ql<=l&&r<=qr){
		while(!S[p].empty()){
			set<pair<int,int> >::iterator t=S[p].begin();
			if(t->fi>val)break;
			if(ckmin(dis[t->se],d+a[t->se].C))pq.push(mkp(-dis[t->se],t->se));
			S[p].erase(t);
		}
		return;
	}
	int mid=(l+r)>>1;
	if(ql<=mid)link(ql,qr,val,d,l,mid,lc);
	if(mid<qr)link(ql,qr,val,d,mid+1,r,rc);
}
}T[2];
LL Dij(){
	memset(dis,0x3f,sizeof(dis)),memset(vis,0,sizeof(vis));
	rep(i,1,m)T[0].change(i,a[i].L-a[i].T-1),T[1].change(i,a[i].L+a[i].T-1);
	rep(i,1,m)if(a[i].L==1)pq.push(mkp(-(dis[i]=a[i].C),i));
	while(!pq.empty()){
		int u=pq.top().se;pq.pop();
		if(vis[u])continue;vis[u]=1;
		if(a[u].R==n)return dis[u];
		if(u>1)T[0].link(1,u-1,a[u].R-a[u].T,dis[u]);
		if(u<m)T[1].link(u+1,m,a[u].R+a[u].T,dis[u]);
	}
	return -1;
}
signed main(){
	n=read(),m=read();
	rep(i,1,m)a[i].T=read(),a[i].L=read(),a[i].R=read(),a[i].C=read();
	sort(a+1,a+m+1,cmp),printf("%lld\n",Dij());
	return 0;
}