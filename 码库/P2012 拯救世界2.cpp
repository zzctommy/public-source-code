#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int mod = 1e9;
int qpow(int n, LL k) {
	int res = 1;
	for(; k; k >>= 1, n = 1ll * n * n % mod) 
		if (k & 1) res = 1ll * n * res % mod;
	return res;
}
LL n;
int ans;
void fmod(int&x) {x += x >> 31 & mod, x -= mod, x += x >> 31 & mod;}
signed main() {
	while (~scanf("%lld", &n)) {
		if (! n) break;
		if (n < 4) {puts("0"); continue;}
		ans = 0;
		fmod(ans += 81ll * qpow(12, n - 4)% mod);
		fmod(ans -= qpow(8, n - 2));
		fmod(ans += 6ll * qpow(4, n - 4) % mod);
		fmod(ans += qpow(- 4, n - 4));
		printf("%d\n", ans);
	}
	return 0;
}