#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=500005;
#define mod 998244353
inline void fmod(int&x){x-=mod,x+=x>>31&mod;}
int n,k,m,l[N],r[N],x[N],dif[N],pos[N],ans=1,dp[N];
signed main(){
	n=read(),k=read(),m=read();
	rep(i,1,m)l[i]=read(),r[i]=read(),x[i]=read();
	rep(i,0,k-1){
		rep(j,1,n+1)pos[j]=dif[j]=dp[i]=0;
		rep(j,1,m)
			if(x[j]>>i&1)++dif[l[j]],--dif[r[j]+1];
			else ckmax(pos[r[j]+1],l[j]);
		rep(j,1,n+1)ckmax(pos[j],pos[j-1]),dif[j]+=dif[j-1];
		// cerr<<i<<",pos:";rep(j,1,n)cerr<<pos[j]<<' ';cerr<<'\n';
		// cerr<<i<<",dif:";rep(j,1,n)cerr<<dif[j]<<' ';cerr<<'\n';
		dp[0]=1;
		int res=0,now=1,it=0;
		rep(j,1,n+1){
			if(dif[j]){dp[j]=0;continue;}
			while(it<pos[j])fmod(now+=mod-dp[it]),++it;
			dp[j]=now,fmod(res+=now),fmod(now+=dp[j]);
		}
		// cerr<<i<<", dp:";rep(j,1,n+1)cerr<<dp[j]<<' ';cerr<<'\n';
		ans=1ll*ans*dp[n+1]%mod;
	}
	printf("%d\n",ans);
}