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
const int N=300005;
int n,k,a[N],ans;
vector<int>v;
signed main(){
	n=read(),k=read();
	rep(i,1,n){
		a[i]=read();
		if(i>1)v.pb(a[i-1]-a[i]);
	}
	ans=a[n]-a[1];
	sort(v.begin(),v.end());
	rep(i,0,k-2)ans+=v[i];
	cout<<ans<<'\n';
}