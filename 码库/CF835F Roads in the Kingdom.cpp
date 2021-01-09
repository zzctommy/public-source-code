#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define x first
#define y second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 200005
#define inf 1000000000000000ll
int n;
int loop[N],cnt,val[N],vis[N];
LL sum[N],f[N],ans1,ans2,L[N],R[N],ll[N],rr[N];
int head[N],num_edge;
struct edge{int nxt,to,val;}e[N<<1];
void addedge(int fr,int to,int val){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	e[num_edge].val=val;
	head[fr]=num_edge;
}
int dfs(int u,int ft){
	if(vis[u])return u;
	vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==ft)continue;
		int tmp=dfs(v,u);
		if(tmp){
			loop[++cnt]=u,val[cnt]=e[i].val,vis[u]=2;
			return tmp==u?0:tmp;
		}
	}
	return 0;
}
void getd(int u,int ft){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==ft||vis[v]==2)continue;
		getd(v,u);
		ans1=max(ans1,f[v]+f[u]+e[i].val);
		f[u]=max(f[u],f[v]+e[i].val);
	}
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i){
		int x=read(),y=read(),z=read();
		addedge(x,y,z),addedge(y,x,z);
	}
	dfs(1,0);
	for(int i=1;i<=cnt;++i)getd(loop[i],0);
	for(int i=1;i<=cnt;++i)sum[i]=sum[i-1]+val[i];
	LL tmp;
	L[0]=ll[0]=R[cnt+1]=rr[cnt+1]=-inf;
	tmp=-inf;
	for(int i=1;i<=cnt;++i){
		L[i]=max(L[i-1],f[loop[i]]+sum[i]);
		ll[i]=max(ll[i-1],f[loop[i]]+sum[i]+tmp);
		tmp=max(tmp,f[loop[i]]-sum[i]);
	}//ll[r]=max{f[r]+sum[r]+f[l]-sum[l]}
	tmp=-inf;
	for(int i=cnt;i>=1;--i){
		R[i]=max(R[i+1],f[loop[i]]+sum[cnt]-sum[i]);
		rr[i]=max(rr[i+1],f[loop[i]]-sum[i]+tmp);
		tmp=max(tmp,f[loop[i]]+sum[i]);
	}//ll[l]=max{f[r]+sum[r]+f[l]-sum[l]}
	//both:ans=min{f[l]+sum[l]+f[r]+sum[cnt]-sum[r]}
	ans2=inf;
	for(int i=1;i<=cnt;++i)ans2=min(ans2,max(L[i-1]+R[i],max(ll[i-1],rr[i])));
	printf("%lld\n",max(ans1,ans2));
	return 0;
}