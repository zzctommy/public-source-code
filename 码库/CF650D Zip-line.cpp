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
#define N 800005
int n,m,a[N],b[N],h[N],lsh[N],len,tr1[N],tr2[N],pre[N],suf[N],cnt[N],LIS,ans[N];
void add1(int x,int d){for(int i=x;i<=len;i+=i&-i)tr1[i]=max(d,tr1[i]);}
int ask1(int x){int res=0;for(int i=x;i>0;i-=i&-i)res=max(res,tr1[i]);return res;}
void add2(int x,int d){for(int i=x;i>0;i-=i&-i)tr2[i]=max(tr2[i],d);}
int ask2(int x){int res=0;for(int i=x;i<=len;i+=i&-i)res=max(res,tr2[i]);return res;}
vector<pair<int,int> >q[N];
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i)h[i]=lsh[++len]=read();
	for(int i=1;i<=m;++i)a[i]=read(),b[i]=lsh[++len]=read();
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;++i)h[i]=lower_bound(lsh+1,lsh+len+1,h[i])-lsh;
	for(int i=1;i<=m;++i)b[i]=lower_bound(lsh+1,lsh+len+1,b[i])-lsh,q[a[i]].pb(mkp(b[i],i));
	// for(int i=1;i<=n;++i)std::cerr<<h[i]<<' ';std::cerr<<'\n';
	for(int i=1;i<=n;++i){
		for(pair<int,int>j:q[i])ans[j.y]+=ask1(j.x-1);
		add1(h[i],pre[i]=ask1(h[i]-1)+1),LIS=max(LIS,pre[i]);
	}
	for(int i=n;i>=1;--i){
		for(pair<int,int>j:q[i])ans[j.y]+=ask2(j.x+1);
		add2(h[i],suf[i]=ask2(h[i]+1)+1);
	}
	// std::cerr<<LIS<<'\n';
	// for(int i=1;i<=n;++i)std::cerr<<pre[i]<<' ';std::cerr<<'\n';
	// for(int i=1;i<=n;++i)std::cerr<<suf[i]<<' ';std::cerr<<'\n';
	// for(int i=1;i<=m;++i)std::cerr<<ans[i]<<' ';std::cerr<<'\n';
	for(int i=1;i<=n;++i)if(pre[i]+suf[i]-1==LIS)++cnt[pre[i]];
	for(int i=1;i<=m;++i){
		if(cnt[pre[a[i]]]==1&&pre[a[i]]+suf[a[i]]-1==LIS)printf("%d\n",max(LIS-1,ans[i]+1));
		else printf("%d\n",max(LIS,ans[i]+1));
	}
	return 0;
}