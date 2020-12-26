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
#define per(i,y,x) for(int i=y,i##end=x;i>=i##end;--i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=100005;
const int K=205;
const LL inf=1e18;
int n,k,a[N],H,T,q[N],pre[N][K],id;
LL dp[N][K],s[N],ans;
db slope(int i,int j,int c){
	return s[i]==s[j]?inf:1.*(dp[i][c]-dp[j][c])/(s[i]-s[j]);
}
void print(int n,int k){
	if(k==1)return printf("%d ",n),void();
	print(pre[n][k],k-1);
	printf("%d ",n);
}
signed main(){
	n=read(),k=read();
	rep(i,1,n)a[i]=read(),s[i]=s[i-1]+a[i];
	rep(i,1,n)dp[i][1]=s[i]*(s[n]-s[i]);
	rep(j,2,k){
		H=1,T=0;
		rep(i,1,n){
			while(H<T&&slope(q[H],q[H+1],j-1)>=s[n]-s[i])++H;
			dp[i][j]=dp[q[H]][j-1]+(s[i]-s[q[H]])*(s[n]-s[i]),pre[i][j]=q[H];
			while(H<T&&slope(q[T-1],q[T],j-1)<=slope(q[T-1],i,j-1))--T;
			q[++T]=i;
		}
	}
	rep(i,1,n)if(ckmax(ans,dp[i][k]))id=i;
	printf("%lld\n",ans);
	print(id,k),puts("");
	return 0;
}