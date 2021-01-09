#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline unsigned read() {
	unsigned x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N = 20005;
const int M = 100005;
const int mod = 1ll << 31;
int ans[N], tr[M];
bool vis[M];
int mu[M], pri[M], cnt, q, it = 1;
struct node {
	int n, m, a, id;
	inline bool operator<(const node&rhs)const{return a < rhs.a;}
}a[N];
struct fact {
	int id, x;
	inline bool operator<(const fact&rhs)const{return x < rhs.x;}
}f[M];
void add(int x, int d) {
	for (int i = x; i < M; i += i & -i) tr[i] += d;
}
int ask(int x) {
	int res = 0;
	for (int i = x; i > 0; i -= i & -i) res += tr[i];
	return res;
}
void Sieve() {
	mu[1] = 1;
	for (int i = 2; i < M; ++ i) {
		if (! vis[i]) pri[++ cnt] = i, mu[i] = -1;
		for (int j = 1; i * pri[j] < M; ++ j) {
			vis[i * pri[j]] = 1;
			if(i % pri[j] == 0) break;
			mu[i * pri[j]] = - mu[i];
		}
	}
	for (int i = 1; i < M; ++ i) 
		for (int j = 1; i * j < M; ++ j)
			f[i * j].x += i;
	for(int i = 1; i < M; ++ i) f[i].id = i;
	sort(f + 1, f + M);
}
signed main() {
	Sieve();
	q = read();
	for (int i = 1; i <= q; ++ i)
		a[i].n = read(), a[i].m = read(), a[i].a = read(), a[i].id = i;
	sort(a + 1, a + q + 1);
	for (int i = 1; i <= q; ++ i) {
		while (it < M && f[it].x <= a[i].a) {
			int t = f[it].id;
			for (int j = 1; j * t < M; ++ j) add(j * t, f[it].x * mu[j]);
			++ it;
		} 
		int res = 0, n = a[i].n, m = a[i].m;
		if (n > m) swap(n, m);
		for (int l = 1, r; l <= n; l = r + 1)
			r = min(n / (n / l), m / (m / l)), res += (n / l) * (m / l) * (ask(r) - ask(l - 1));
		ans[a[i].id] = res;
	}
	for (int i = 1; i <= q; ++ i) printf("%lld\n", ans[i] % mod);
	return 0;
}
/*
1
25291 26958 42646

235628669
*/