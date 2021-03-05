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
int n,a[N],cnt[N],L[N],R[N],suf[N],ans=N,f[N];
signed main(){
	n=read();
	rep(i,1,n)a[i]=read();
	rep(i,1,n)R[a[i]]=i;
	per(i,n,1)L[a[i]]=i;
	per(i,n,1)++cnt[a[i]],suf[i]=max(suf[i+1],cnt[a[i]]);
	rep(i,1,n){
		f[i]=f[i-1];
		if(i==R[a[i]])ckmax(f[i],f[L[a[i]]-1]+cnt[a[i]]);
		ckmin(ans,n-f[i]-suf[i+1]);
	}
	cout<<ans<<'\n';
}