#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
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
const int N=100005;
vector<int>g[N];
int n,dep[N];
double ans;
void dfs(int u,int ft){
	dep[u]=dep[ft]+1;
	for(int v:g[u]){
		if(v==ft)continue;
		dfs(v,u);
	}
}
signed main(){
	n=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		g[x].pb(y),g[y].pb(x);
	}
	dfs(1,0);
	for(int i=1;i<=n;++i)ans+=1./dep[i];
	printf("%.10lf\n",ans);
	return 0;
}