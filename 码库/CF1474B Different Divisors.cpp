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
int d;
bool vis[N];
int pri[N/10],pct;
void Sieve(const int&n=N-1){
	for(int i=2;i<=n;++i){
		if(!vis[i])pri[++pct]=i;
		for(int j=1;j<=pct&&i*pri[j]<=n;++j){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0)break;
		}
	}
}
void Main(){
	d=read();
	int A,B;
	for(int i=d+1;;++i)if(!vis[i]){A=i;break;}
	for(int i=A+d;;++i)if(!vis[i]){B=i;break;}
	printf("%lld\n",1ll*A*B);
}
signed main(){Sieve();
for(int T=read();T;--T)Main();}
/*
5
1
0
3
011
3
110
6
111000
6
001011

*/