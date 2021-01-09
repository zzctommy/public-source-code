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
const int N = 100005;
int n, a[N], ans, b[N];
map<int,int>to;
signed main() {
	n = read();
	rep (i, 1, n) a[i] = b[i] = read();
	sort (b + 1, b + n + 1);
	rep (i, 1, n) to[b[i]] = i;
	rep (i, 1, n) if( (i & 1) != (to[a[i]] & 1)) ++ans;
	printf("%d\n",ans >> 1);
	return 0;
}