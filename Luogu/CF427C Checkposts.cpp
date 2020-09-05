#include<bits/stdc++.h>
using namespace std;
#define rint register int
typedef long long LL;
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
const int N=100010;
const int M=300010;
const int mod=1000000007;
const int inf=1000000009;
struct edge{
	int nxt,to;
}e[M];
int head[N],num_edge,w[N];
int n,m,st[N],top,mi[N],sum[N],C,dfstim,low[N],dfn[N],scc[N];
LL ans1,ans2=1;
void addegde(int from,int to) {
	++num_edge;
	e[num_edge].nxt=head[from];
	e[num_edge].to=to;
	head[from]=num_edge;
}
void tarjan(int u) {
	low[u]=dfn[u]=++dfstim;
	st[++top]=u;
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
		else if(!scc[v])low[u]=min(low[u],dfn[v]);
	} 
	if(low[u]==dfn[u]) {
		++C,scc[u]=C;
		mi[C]=w[u],sum[C]=1;
		while(st[top]!=u) {
			scc[st[top]]=C;
			if(w[st[top]]==mi[C])++sum[C];
			else if(w[st[top]]<mi[C])mi[C]=w[st[top]],sum[C]=1;
			--top;
		}
		--top;
	}
}
signed main() {
	n=rd();for(rint i=1;i<=n;++i)w[i]=rd();
	m=rd();for(rint i=1,x,y;i<=m;++i)x=rd(),y=rd(),addegde(x,y);
	for(rint i=1;i<=n;++i)if(!dfn[i])tarjan(i);
	for(rint i=1;i<=C;++i)ans1+=mi[i],ans2=1ll*ans2*sum[i]%mod;
	printf("%lld %lld\n",ans1,ans2);return 0;
}