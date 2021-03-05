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
int n,a[N],to[N];
bool vis[N];
void Main(){
	n=read();
	rep(i,1,n)a[i]=read(),vis[i]=0,to[a[i]]=i;
	int lst=n;
	per(i,n,1){
		if(!vis[i]){
			rep(j,to[i],lst)printf("%d ",a[j]),vis[a[j]]=1;
			lst=to[i]-1;
		}
	}
	puts("");
}
signed main(){
	for(int T=read();T;--T)Main();
}