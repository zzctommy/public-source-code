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
#define N 500005
int n,m,a[N],dif[N],ans[N];
int okl[N],okr[N],bnl[N],bnr[N];
vector<int>v;
bool vis[N];
signed main(){
	n=read(),m=read();
	for(int i=0;i<=n;++i)okl[i]=0,okr[i]=n,bnl[i]=n,bnr[i]=0;
	for(int i=1;i<=m;++i){
		int l=read(),r=read(),v=read();
		if(v)okl[v-1]=max(okl[v-1],l),okr[v-1]=min(okr[v-1],r);
		else ++dif[l],--dif[r+1];
		bnl[v]=min(bnl[v],l),bnr[v]=max(bnr[v],r);
	}
	for(int i=1;i<=n;++i)dif[i]+=dif[i-1];
	for(int i=n-1;i>=0;--i){
		okl[i]=max(okl[i+1],okl[i]);
		okr[i]=min(okr[i+1],okr[i]);
		if(okl[i]>okr[i])return puts("-1"),0;
	}
	for(int i=okl[0];i<=okr[0];++i)
		if(!dif[i])v.pb(i),vis[i]=1;
	if(v.empty())return puts("-1"),0;
	ans[v.back()]=0,v.pop_back();
	for(int i=okl[0];i<=okr[0];++i)
		if(!vis[i])v.pb(i),vis[i]=1;
	for(int i=1;i<=n;++i){
		if(bnl[i]<=bnr[i]){
			for(int j=okl[i];j<bnl[i]&&j<=okr[i]&&!vis[j];++j)v.pb(j),vis[j]=1;
			for(int j=okr[i];j>bnr[i]&&j>=okl[i]&&!vis[j];--j)v.pb(j),vis[j]=1;
		}
		if(v.empty()||(bnl[i]<=v.back()&&v.back()<=bnr[i]))return puts("-1"),0;
		ans[v.back()]=i,v.pop_back();
		for(int j=max(okl[i],bnl[i]);j<=okr[i]&&!vis[j];++j)v.pb(j),vis[j]=1;
		for(int j=min(okr[i],bnr[i]);j>=okl[i]&&!vis[j];--j)v.pb(j),vis[j]=1;
	}
	for(int i=0;i<=n;++i)printf("%d%c",ans[i]," \n"[i==n]);
	return 0;
}
/*
3 0 2 1 4 5
5 7
1 2 1
0 2 1
0 3 4
1 3 3
0 5 6
4 5 0
2 3 0

*/