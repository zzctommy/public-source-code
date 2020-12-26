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
unsigned int a0=0,a1=-1,ans;
int n,m;
signed main(){
	n=read(),m=read();
	rep(i,1,n){
		static char str[5];static int x;
		scanf("%s%d",str,&x);
		if(str[0]=='A')a0&=x,a1&=x;
		else if(str[0]=='O')a0|=x,a1|=x;
		else if(str[0]=='X')a0^=x,a1^=x;
	}
	for(int i=30;i>=0;--i)
		if(a0>>i&1)ans+=1<<i;
		else if(a1>>i&1&&m>=(1<<i))ans+=1<<i,m-=1<<i;
	printf("%u\n",ans);
	return 0;
}