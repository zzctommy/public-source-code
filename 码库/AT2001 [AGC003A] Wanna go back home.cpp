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
const int N = 114514;
int n, cnt[5];
char str[N];
signed main() {
	scanf("%s", str + 1) ,n = strlen(str + 1);
	rep (i, 1, n) 
		if (str[i] == 'E') ++cnt[0];
		else if (str[i] == 'W') ++cnt[1];
		else if (str[i] == 'S') ++cnt[2];
		else ++cnt[3];
	if ((cnt[0] && !cnt[1]) || (cnt[1] && !cnt[0]) || (cnt[2] && !cnt[3]) || (cnt[3] && !cnt[2])) puts("No");
	else puts("Yes");
}