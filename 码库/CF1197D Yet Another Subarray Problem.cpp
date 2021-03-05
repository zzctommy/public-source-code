#include<bits/stdc++.h>
#define ll long long
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define _rep(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define mod 998244353
typedef std::pair<int,int> pii;
inline int upd(const int x){return x+(x>>31&mod);}
inline void reduce(int&x){x-=mod,x+=x>>31&mod;}
inline void add(int&x,const int y){x=upd((x+y)%mod);}

const int N = 300005;
const int T = N << 2;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int a[N], n, m, k;
ll s[N], ans, t[20];

int main(){
	std::ios::sync_with_stdio(0);
	std::cin.tie(0), std::cout.tie(0);
	std::cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i)
	   	std::cin >> a[i], s[i] = s[i - 1] + a[i];
	memset(t, 0x3f, sizeof(t));
	t[0] = k;
	for (int i = 1; i <= n; ++i) {
		ll mi = inf;
		for (int j = 0; j < m; ++j) mi = std::min(mi, t[j]);
		ans = std::max(ans, s[i] - mi);
		int bl = i % m;
		t[bl] = std::min(t[bl], s[i]) + k;
	}
	printf("%lld\n", ans);
	return 0;
}