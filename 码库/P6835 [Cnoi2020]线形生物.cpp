#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N = 1000005;
const int zky = 998244353;
int n, m, s[N];
vector<int>g[N];
signed main() {
	read(), n = read(), m = read();
	for (int i = 1; i <= m; ++ i) {
		int u = read(), v = read();
		g[u].pb(v);
	}
	for (int i = 1; i <= n; ++ i) {
		int sum = 1;
		for (int j : g[i]) (sum += s[i - 1] - s[j - 1] + 1) %= zky;
		s[i] = (s[i - 1] + sum) % zky;
	}
	printf("%lld\n", (s[n] + zky) % zky);
	return 0;
}
