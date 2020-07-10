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
const int N=1e6+10;
int n,siz[N];
LL ans;
int head[N],num_edge;
struct edge {
	int val,to,nxt;
}e[N<<1];
void addedge(int from,int to,int val) {
	++num_edge;
	e[num_edge].nxt=head[from];
	e[num_edge].to=to;
	e[num_edge].val=val;
	head[from]=num_edge;
}
void dfs(int u,int ft) {
	siz[u]=1;
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft)continue;
		dfs(v,u);
		siz[u]+=siz[v];
		ans+=1ll*e[i].val*abs(n-(siz[v]<<1));
	}
} 
signed main() {
	n=rd();
	for(rint i=1;i<n;++i) {
		int x=rd(),y=rd(),z=rd();
		addedge(x,y,z),addedge(y,x,z);
	}
	dfs(1,0);
	cout<<ans<<endl;
	return 0;
}
