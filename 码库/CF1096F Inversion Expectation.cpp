#include<bits/stdc++.h>
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
const int N=200005;
const int mod=998244353;
int n,a[N],tr[N],m,ans,cnt[N];
void add(int x,int d){
	for(int i=x;i<=n;i+=i&-i)tr[i]+=d;
}
int ask(int x){
	int res=0;
	for(int i=x;i>0;i-=i&-i)res+=tr[i];
	return res;
}
void fmod(int&x){
	x+=x>>31&mod,x-=mod,x+=x>>31&mod;
}
int qpow(int x,int y,int ret=1){
	for(;y;y>>=1,x=1ll*x*x%mod) if(y&1)
		ret=1ll*ret*x%mod; return ret;
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i)a[i]=read(),m+=!~a[i];
	ans=1ll*m*(m-1)/2%mod*((mod+1)>>1)%mod;
	for(int i=n;i>=1;--i)if(~a[i])fmod(ans+=ask(a[i])),add(a[i],1),++cnt[a[i]];
	for(int i=1;i<=n;++i)cnt[i]+=cnt[i-1];
	int sum=0;
	for(int i=1,t=0;i<=n;++i)
		if(~a[i])fmod(sum+=1ll*t*(m-a[i]+cnt[a[i]])%mod);
		else ++t;
	for(int i=n,t=0;i>=1;--i)
		if(~a[i])fmod(sum+=1ll*t*(a[i]-cnt[a[i]])%mod);
		else ++t;
	fmod(ans+=1ll*sum*qpow(m,mod-2)%mod);
	std::cout<<ans<<'\n';
	return 0;
}
/*
10
-1 2 -1 4 5 -1 10 -1 9 -1
199648886
*/