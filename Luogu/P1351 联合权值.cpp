#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
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
const int mod=10007;
int n,w[N],ans1,ans2; 
struct edge{
	int nxt,to;
}e[N<<1];
int head[N],num_edge;
void addedge(int fr,int to){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
void dfs(int u,int ft){
	vector<int>t;int cnt=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==ft)continue;
		++cnt,dfs(v,u),t.push_back(w[v]);
	}
	for(int i=0,mx=0;i<cnt;++i){
		ans1=max(ans1,max(mx*t[i],w[ft]*t[i])),mx=max(mx,t[i]),ans2=(ans2+t[i]*w[ft])%mod;
		if(i)ans2=(ans2+t[i-1]*t[i])%mod,t[i]=(t[i]+t[i-1])%mod;
	}
}
signed main(){
	n=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		addedge(x,y),addedge(y,x);
	}
	for(int i=1;i<=n;++i)w[i]=read();
	dfs(1,0);
	printf("%d %d\n",ans1,ans2*2%mod);
	return 0;
}