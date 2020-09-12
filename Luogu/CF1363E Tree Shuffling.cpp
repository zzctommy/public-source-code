#include<bits/stdc++.h>
using namespace std;
#define int long long
int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
#define N 200009
int n,a[N],b[N],c[N];
int tag[N],mi[N],s[2][N],ans;
vector<int>g[N];
void dfs(int u,int ft) {
	if(a[u]>mi[u])tag[u]=1;
	if(b[u]!=c[u])++s[b[u]][u];
	for(int v:g[u])if(v!=ft) {
		mi[v]=min(a[v],mi[u]),dfs(v,u);
		s[0][u]+=s[0][v],s[1][u]+=s[1][v];
	}
	if(!tag[u]) {
		int k=min(s[0][u],s[1][u]);
		ans+=2*a[u]*k,s[0][u]-=k,s[1][u]-=k;
	}
}
signed main() {
	n=rd();
	for(int i=1;i<=n;++i)a[i]=rd(),b[i]=rd(),c[i]=rd();
	for(int i=1;i<n;++i) {
		int x=rd(),y=rd();
		g[x].push_back(y),g[y].push_back(x);
	}
	mi[1]=a[1],dfs(1,0);
	if(s[0][1]||s[1][1])puts("-1");
	else printf("%lld\n",ans);
	return 0;
}