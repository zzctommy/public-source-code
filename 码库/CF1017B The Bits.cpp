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
const int N=100005;
char S[N],T[N];
int n,c1,c2,c3,c4;
signed main(){
	scanf("%lld%s%s",&n,S+1,T+1);
	rep(i,1,n){
		if(S[i]=='0')++c1;
		if(S[i]=='1')++c2;
		if(S[i]=='0'&&T[i]=='0')++c3;
		if(S[i]=='1'&&T[i]=='0')++c4;
	}
	printf("%lld\n",c2*c3+c1*c4-c3*c4);
}