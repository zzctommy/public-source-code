#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define mkp(x,y) make_pair(x,y)
#define fi first
#define se second
#define pb(x) push_back(x)
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define N 100005
int n,q,v[N],c[N];
LL dp[N],f[N];
void solve(int a,int b){
	memset(f,-0x3f,sizeof(f));
	f[0]=0;
	int id[2];
	id[0]=0,id[1]=-1;
	for(int i=1;i<=n;++i){
		dp[i]=f[c[i]]+1ll*a*v[i];
		if(id[0]!=c[i])dp[i]=max(dp[i],f[id[0]]+1ll*b*v[i]);
		else if(~id[1])dp[i]=max(dp[i],f[id[1]]+1ll*b*v[i]);
		if(dp[i]>f[c[i]]){
			f[c[i]]=dp[i];
			if(id[0]==c[i])continue;
			if(f[id[0]]<f[c[i]])id[1]=id[0],id[0]=c[i];
			else if(f[id[1]]<f[c[i]])id[1]=c[i];
		}
	}
	LL res=0;
	for(int i=0;i<=n;++i)res=max(res,dp[i]);
	printf("%lld\n",res);
}
signed main(){
	n=read(),q=read();
	for(int i=1;i<=n;++i)v[i]=read();
	for(int i=1;i<=n;++i)c[i]=read();
	while(q--){
		int x=read(),y=read();
		solve(x,y);
	}
}