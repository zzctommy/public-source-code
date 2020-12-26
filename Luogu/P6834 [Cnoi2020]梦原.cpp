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
#define mod 998244353
void fmod(int&x){x-=mod,x+=x>>31&mod;}
int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
const int N=1000005;
int n,k,a[N],ans,b[N],lsh[N],len;
struct BIT{
int tr[N];
BIT(){memset(tr,0,sizeof(tr));}
void add(int x,int d){for(int i=x;i<=n;i+=i&-i)fmod(tr[i]+=d);}
int ask(int x){int res=0;for(int i=x;i>0;i-=i&-i)fmod(res+=tr[i]);return res;}
}tr[2];
signed main(){
	n=read(),k=read();
	rep(i,1,n)a[i]=lsh[i]=read();
	sort(lsh+1,lsh+n+1),len=unique(lsh+1,lsh+n+1)-lsh-1;
	rep(i,1,n)b[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
	ans=a[1],tr[0].add(b[1],a[1]),tr[1].add(b[1],1);
	rep(i,2,n){
		int num=i-max(i-k,1),sum=(1ll*tr[1].ask(b[i])*a[i]%mod-tr[0].ask(b[i])+mod)%mod;
		fmod(ans+=1ll*sum*qpow(num,mod-2)%mod);
		if(i>k)tr[0].add(b[i-k],mod-a[i-k]),tr[1].add(b[i-k],-1);
		tr[0].add(b[i],a[i]),tr[1].add(b[i],1);
	}
	printf("%d\n",ans);
	return 0;
}