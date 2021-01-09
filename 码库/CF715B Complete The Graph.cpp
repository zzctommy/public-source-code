#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define fi first
#define se second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
#define int long long
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 1005
#define M 10005
#define inf 100000000000000ll
int n,m,L,S,T,head[N],dis[N];
bool vis[N];
struct edge{
	int fr,nxt,to,val,flg;
}e[M<<1];
int check(int k){
	priority_queue<pair<int,int> >pq;
	for(int i=0;i<n;++i)vis[i]=0,dis[i]=inf;
	pq.push(mkp(dis[S]=0,S));
	while(!pq.empty()){
		int u=pq.top().se;pq.pop();
		if(vis[u])continue;vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to,w=e[i].flg?k/m+(k%m>=(i-1)%m+1):e[i].val;
			if(dis[v]>dis[u]+w)dis[v]=dis[u]+w,pq.push(mkp(-dis[v],v));
		}
	}
	// cerr<<"k="<<k<<":";for(int i=0;i<n;++i)cerr<<dis[i]<<' ';cerr<<'\n';
	return dis[T];
}
signed main(){
	n=read(),m=read(),L=read(),S=read(),T=read();
	for(int i=1;i<=m;++i){
		e[i].fr=read(),e[i].to=read(),e[i].val=read(),e[i].nxt=head[e[i].fr],head[e[i].fr]=i;
		e[i].flg=!e[i].val;
		e[i+m].fr=e[i].to,e[i+m].to=e[i].fr,e[i+m].val=e[i].val,e[i+m].nxt=head[e[i+m].fr],head[e[i+m].fr]=i+m;
		e[i+m].flg=!e[i+m].val;
	}
	int l=m,r=m*L;
	while(l<=r){
		int mid=(l+r)>>1,k=check(mid);
		if(k==L){
			puts("YES");
			for(int i=1;i<=m;++i)
				printf("%lld %lld %lld\n",e[i].fr,e[i].to,e[i].flg?mid/m+(mid%m>=(i-1)%m+1):e[i].val);
			return 0;
		}
		if(k<L)l=mid+1;
		else r=mid-1;
	}
	puts("NO");
}