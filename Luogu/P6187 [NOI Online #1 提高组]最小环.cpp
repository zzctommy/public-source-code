#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define x first
#define y second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 200005
int n,m,a[N];
LL ans[N];
int gcd(int x,int y){return !y?x:gcd(y,x%y);}
LL f(int x){
	if(!x){
		if(ans[0])return ans[0];
		for(int i=1;i<=n;++i)ans[0]+=1ll*a[i]*a[i];
		return ans[0];
	}
	int len=n/gcd(n,x);
	if(ans[len])return ans[len];
	LL res=0;
	for(int i=1;i<=n;i+=len){
		for(int j=i;j<i+len-2;++j)
			res+=1ll*a[j]*a[j+2];
		res+=1ll*a[i+1]*a[i]+1ll*a[i+len-1]*a[i+len-2];
	}
	return ans[len]=res;
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i)a[i]=read();
	sort(a+1,a+n+1);
	while(m--)printf("%lld\n",f(read()));
	return 0;
}