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
#define per(i,y,x) for(int i=y,i##end=x;i>=i##end;--i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
#define N 200005
int n,c[2], s[2];
char str[N];
signed main() {
	scanf("%d%s", &n, str + 1);
	rep(i, 1, n){
		if (str[i] != '?') s[i > n / 2] += str[i] - '0';
		else ++ c[i > n / 2];
	}
	c[0] >>= 1, c[1] >>= 1;
	if (s[0] + c[0] * 9 == s[1] + c[1] * 9) puts("Bicarp");
	else puts("Monocarp");
}