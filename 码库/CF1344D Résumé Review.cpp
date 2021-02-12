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
const int N=100005;
int n,a[N],b[N];
pair<LL,int>c[N];
LL k,sum;
bool check(LL o){
	LL res=0;
	for(int i=1;i<=n;++i){
		int l=0,r=a[i],t=0;
		while(l<=r){
			LL mid=(l+r)>>1;
			if(-3ll*mid*mid-3ll*mid-1ll+a[i]>=o)l=mid+1,t=mid;
			else r=mid-1;
		}
		res+=t;
	}
	return res>=k;
}
signed main(){
	cin>>n>>k;
	rep(i,1,n)a[i]=read();
	LL l=-3.5e18,r=3.5e18,res=114514;
	while(l<=r){
		LL mid=(l+r)>>1;
		if(check(mid))l=mid+1,res=mid;
		else r=mid-1;
	}
	for(int i=1;i<=n;++i){
		int l=0,r=a[i],t=0;
		while(l<=r){
			LL mid=(l+r)>>1;
			if(-3ll*mid*mid-3ll*mid-1ll+a[i]>=res)l=mid+1,t=mid;
			else r=mid-1;
		}
		b[i]=t,sum+=b[i];
		if(t>0)c[i]=mkp(-3ll*t*t+3ll*t-1ll+a[i],i);
		else c[i]=mkp(4e18,i);
	}
	sort(c+1,c+n+1);
	rep(i,1,sum-k)--b[c[i].se];
	LL qwq=0;
	rep(i,1,n)qwq+=1ll*b[i]*(a[i]-1ll*b[i]*b[i]);
	cerr<<qwq<<'\n';
	rep(i,1,n)printf("%d ",b[i]);
	return 0;
}