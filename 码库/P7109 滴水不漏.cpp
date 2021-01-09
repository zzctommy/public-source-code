//Orz cyn2006
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
const int N=1005;
int n,s[N],it=1;
int ask(int x,int y){printf("? %d %d\n",x,y),fflush(stdout);return read();}
void solve(int x){
	while(it<x)if(ask(it++,x)){--it;break;}
	int l=1,r=it,res=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(ask(it,mid))l=mid+1,res=mid;
		else r=mid-1;
		ask(mid,it);
	}
	s[x]=res;
	rep(i,it+1,x)s[x]+=i;
	// cerr<<it<<' '<<x<<' '<<s[x]<<'\n';
}
signed main(){
	n=read();
	s[1]=ask(1,1);
	for(int i=2;i<=n;++i)solve(i);
	printf("!");rep(i,1,n)printf(" %d",s[i]-s[i-1]);puts(""),fflush(stdout);
}