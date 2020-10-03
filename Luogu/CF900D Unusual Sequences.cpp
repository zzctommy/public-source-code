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
const int mod = 1e9 + 7;
int x, y, ans, tmp;
int cnt, fac[114514];
int qpow(int n, int k) {
	int res = 1;
	while (k) {
		if (k & 1) res = res * n % mod;
		n = n * n % mod, k >>= 1;
	}
	return res;
}
void dfs(int u, int stp, int now) {
	if(u==cnt+1) {
		if (stp) (ans += qpow(2, now - 1)) %= mod;
		else (ans -= qpow (2, now - 1)) %= mod;	
		return;
	}
	dfs(u + 1, stp ^ 1, now / fac[u]);
	dfs(u + 1, stp, now);
}
signed main() {
	cin >> x >> y;
	if (y % x) return cout << 0, 0;
	y /= x, tmp = y;
	for (int i = 2; i * i <= tmp; ++ i) {
		if (tmp % i) continue;
		++ cnt, fac[cnt] = i;
		while(tmp % i == 0) tmp /= i;
	}
	if(tmp > 1) fac[++ cnt] = tmp;
	dfs(1, 1, y);
	cout << (ans + mod) % mod<< endl;
	return 0;
}
