#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef long double db;
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
int n,tot,m;
LL q[N],a[N],cpy[N],ans[N];
void add(LL x,LL tim){
	if(!x)return;
	int i=upper_bound(a+1,a+tot+1,x)-a-1;
	if(!i)ans[x]+=tim;
	else cpy[i]+=x/a[i]*tim,add(x%a[i],tim);
}
signed main(){
	scanf("%d%d",&n,&m);
	rep(i,1,m)scanf("%lld",&q[i]);
	q[0]=n,a[tot=1]=q[m];
	per(i,m-1,0)if(q[i]<a[tot])a[++tot]=q[i];
	reverse(a+1,a+tot+1);
	cpy[tot]=1;
	per(i,tot,2)add(a[i]%a[i-1],cpy[i]+=a[i+1]/a[i]*cpy[i+1]);
	ans[a[1]]+=cpy[1]+=a[2]/a[1]*cpy[2];
	per(i,n,1)ans[i]+=ans[i+1];
	rep(i,1,n)printf("%lld\n",ans[i]);
	return 0;
}