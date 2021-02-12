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
#define int long long
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=505;
int n,a[N],b[N],k,sa,sb,ans;
bool dp[N][N];
signed main(){
	n=read(),k=read();
	rep(i,1,n)a[i]=read(),b[i]=read(),sa+=a[i],sb+=b[i];
	ans=sa/k+sb/k;
	if(ans==(sa+sb)/k)return cout<<ans<<'\n',0;
	sa%=k,sb%=k,dp[0][0]=1;
	rep(i,0,n-1){
		rep(j,0,k)if(dp[i][j]){
			dp[i+1][j]=1;
			rep(l,0,k)if(l<=a[i+1]&&k-l<=b[i+1])
				dp[i+1][(j+l)%k]=1;
		}
		rep(j,k-sb,sa)if(dp[i+1][j])return cout<<ans+1<<'\n',0;
	}
	cout<<ans<<'\n';
}