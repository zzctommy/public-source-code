#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
#define int long long
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=300010;
int n,m;
LL ans,ANS;
struct node {
	int k;LL val;
	node(){}
	node(int o,LL v){k=o,val=v;}
	node operator + (const node &rhs)const{return node(k+rhs.k,val+rhs.val);}
	node operator + (const LL &v)const{return node(k,val+v);}
	bool operator < (const node &rhs)const{return val!=rhs.val?val<rhs.val:k<rhs.k;}
}dp[N][3];
int head[N],num_edge;
struct edge {
	int nxt,val,to;
}e[N<<1];
void addedge(int fr,int to,int val) {
	++num_edge;
	e[num_edge].val=val;
	e[num_edge].to=to;
	e[num_edge].nxt=head[fr];
	head[fr]=num_edge;
}
void dfs(int u,int ft,LL sl) {
	dp[u][0]=dp[u][1]=node(0,0);
	if(sl<0)dp[u][2]=node(1,-sl);
	else dp[u][2]=node(0,0);
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft)continue;
		dfs(v,u,sl);
		dp[u][2]=max(dp[u][2],max(dp[u][2]+dp[v][0],dp[u][1]+dp[v][1]+e[i].val+node(1,-sl)));
		dp[u][1]=max(dp[u][1],max(dp[u][1]+dp[v][0],dp[u][0]+dp[v][1]+e[i].val));
		dp[u][0]=max(dp[u][0],dp[u][0]+dp[v][0]);
	}
	dp[u][0]=max(dp[u][0],max(node(0,0),max(dp[u][1]+node(1,-sl),dp[u][2])));
}
int check(LL sl) {
	dfs(1,0,sl);
	ANS=dp[1][0].val;return dp[1][0].k;
}
signed main() {
	n=rd(),m=rd()+1;
	for(int i=1;i<n;++i) {
		int u=rd(),v=rd(),d=rd();
		addedge(u,v,d),addedge(v,u,d);
	}
	LL l=-1e13,r=1e13;
	while(l<=r) {
		LL mid=(l+r)>>1;int k=check(mid);
		if(k>=m)ans=ANS+1ll*mid*m,l=mid+1;
		else r=mid-1;
	}
	printf("%lld\n",ans);
	return 0;
}