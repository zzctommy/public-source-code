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
#define uint unsigned int
uint seed;
inline uint getnext(){
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
}
const int N=20000005;
uint n,a[N],pri[N/10],pct,ans;
bool vis[N];
signed main(){
	cin>>n>>seed;
	rep(i,1,n)a[i]=getnext();
	for(int i=2;i<=n;++i){
		if(!vis[i])pri[++pct]=i;
		for(int j=1;j<=pct&&i*pri[j]<=n;++j){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0)break;
		}
	}
	for(int i=1;i<=pct;++i)
		for(int j=1;j*pri[i]<=n;++j)
			a[j*pri[i]]+=a[j];
	for(int i=1;i<=n;++i)ans=ans^a[i];
	cout<<ans<<'\n';
	return 0;
}