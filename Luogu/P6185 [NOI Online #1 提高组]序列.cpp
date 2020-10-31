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
const int N=100005;
int n,m,a[N],bl[N],cnt,c[N];
bool tag[N],Tag;
LL sum[2],v[N];
std::vector<pair<int,int> >E;
std::vector<int>g[N],e[N];
void clear(){
	cnt=0,E.clear();
	for(int i=1;i<=n;++i)g[i].clear(),e[i].clear(),bl[i]=tag[i]=v[i]=0,c[i]=-1;
}
void dfs1(int u){
	bl[u]=cnt,v[cnt]+=a[u];
	for(int v:g[u])if(!bl[v])dfs1(v);
}
bool dfs2(int u,int col){
	if(~c[u])return c[u]==col;
	sum[col]+=v[u],c[u]=col,Tag|=tag[u];
	bool flg=1;
	for(int v:e[u])if(!~c[v])flg&=dfs2(v,col^1);
	return flg;
}
void Main(){
	n=read(),m=read(),clear();
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<=n;++i)a[i]=read()-a[i];
	for(int i=1;i<=m;++i){
		int t=read()-1,x=read(),y=read();
		if(!t)E.pb(mkp(x,y));
		if(t)g[x].pb(y),g[y].pb(x);
	}
	for(int i=1;i<=n;++i)if(!bl[i])++cnt,dfs1(i);
	for(std::pair<int,int>i:E){
		if(bl[i.x]==bl[i.y])tag[bl[i.x]]=1;
		else e[bl[i.x]].pb(bl[i.y]),e[bl[i.y]].pb(bl[i.x]);
	}
	for(int i=1;i<=cnt;++i){
		if(!~c[i]){
			sum[0]=sum[1]=Tag=0;
			if(dfs2(i,0)){
				if(Tag){if((sum[0]-sum[1])%2)return puts("NO"),void();}
				else if(sum[0]!=sum[1])return puts("NO"),void();
			} else if((sum[0]-sum[1])%2)return puts("NO"),void();
		}
	}
	puts("YES");
}
signed main(){for(int T=read();T;--T)Main();}