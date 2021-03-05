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
#define int long long
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=105;
int n,a[N],k;
void Main(){
	n=read(),k=read();
	rep(i,1,n)a[i]=read();
	a[n+1]=0;
	while(1){
		int i=1;
		for(i=1;i<=n;++i){
			if(a[i]<a[i+1]){
				++a[i];break;
			}
		}
		if(i==n+1)return puts("-1"),void();
		if(!--k)return printf("%lld\n",i),void();
	}
}
signed main(){for(int T=read();T;--T)Main();}