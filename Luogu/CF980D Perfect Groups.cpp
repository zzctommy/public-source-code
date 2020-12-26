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
const int N=5005;
int n,a[N],pre[N],ans[N];
void f(int&n){
	int tmp=abs(n);
	for(int i=2;i*i<=tmp;++i)
		while(n%(i*i)==0)n/=i*i;
}
signed main(){
	n=read();
	rep(i,1,n)f(a[i]=read());
	rep(i,1,n)per(j,i-1,1)if(a[j]==a[i]){pre[i]=j;break;}
	rep(i,1,n){
		int now=0;
		rep(j,i,n){
			if(pre[j]<i&&a[j])++now;
			now?++ans[now]:++ans[1];
		}
	}
	rep(i,1,n)printf("%d ",ans[i]);
	return 0;
}