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
const int N=200005;
int n,m,a[N],b[N],ans;
char S[N],T[N];
signed main(){
	n=read(),m=read(),scanf("%s%s",S+1,T+1);
	memset(a,0x3f,sizeof(a));
	int it=1;
	rep(i,1,n){
		if(S[i]==T[it])a[it]=i,++it;
	}
	it=m;
	per(i,n,1){
		if(S[i]==T[it])b[it]=i,--it;
	}
	rep(i,1,m-1)ckmax(ans,b[i+1]-a[i]);
	cout<<ans<<'\n';
	return 0;
}