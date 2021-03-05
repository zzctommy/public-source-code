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
#define mod 998244353
const int N = 100005;
const int T = N << 3;
LL f[T], g[T], tg1[T], tg2[T], sum[T], pw;
int n, m;
#define lc(p) ((p) << 1)
#define rc(p) ((p) << 1 | 1)
void pushup(int p) {
	sum[p] = (sum[lc(p)] + sum[rc(p)] + f[p]) % mod;
}
void build(int l = 1, int r = n, int p = 1) {
	f[p] = 0, g[p] = 1, tg1[p] = tg2[p] = 1, sum[p] = 0;
	if(l == r) return;
	int mid = (l + r) >>1;
	build(l, mid, lc(p)), build(mid + 1, r, rc(p));
}
void addtg1(int p, int d) {
	tg1[p] = 1ll * tg1[p] * d % mod;
	f[p] = 1ll * f[p] * d % mod;
	sum[p] = 1ll * sum[p] * d % mod;
}
void addtg2(int p, int d) {
	tg2[p] = 1ll * tg2[p] * d % mod;
	g[p] = 1ll * g[p] * d % mod;
}
void pushdown(int p) {
	if(tg1[p] != 1)
		addtg1(lc(p), tg1[p]), addtg1(rc(p), tg1[p]), tg1[p] = 1;
	if(tg2[p] != 1)
		addtg2(lc(p), tg2[p]), addtg2(rc(p), tg2[p]), tg2[p] = 1;
}
void update(int ql, int qr, int l = 1, int r = n, int p = 1) {
	pushdown(p);
	if(ql <= l && r <= qr) {
		f[p] = (f[p] + pw) % mod;
		addtg1(lc(p), 2), addtg1(rc(p), 2), pushup(p);
		return;
	}
	int mid = (l + r) >> 1;
	g[p] = (g[p] + pw) % mod;
	if(qr <= mid) {
		update(ql, qr, l, mid, lc(p));
		f[rc(p)] = (pw - g[rc(p)] + f[rc(p)] + mod) % mod, g[rc(p)] = 2ll * g[rc(p)] % mod;
		pushdown(rc(p));
		addtg1(lc(rc(p)), 2), addtg2(lc(rc(p)), 2);
		addtg1(rc(rc(p)), 2), addtg2(rc(rc(p)), 2);
		pushup(rc(p)), pushup(p);
		return;
	}
	if(ql > mid) {
		update(ql, qr, mid + 1, r, rc(p));
		f[lc(p)] = (pw - g[lc(p)] + f[lc(p)] + mod) % mod, g[lc(p)] = 2ll * g[lc(p)] % mod;
		pushdown(lc(p));
		addtg1(lc(lc(p)), 2), addtg2(lc(lc(p)), 2);
		addtg1(rc(lc(p)), 2), addtg2(rc(lc(p)), 2);
		pushup(lc(p)), pushup(p);
		return;
	}
	update(ql, qr, l, mid, lc(p)), update(ql, qr, mid + 1, r, rc(p));
	pushup(p);
}
signed main() {
	n = read(), m = read();
	build(), pw = 1;
	for(int i = 1; i <= m; ++i) {
		int op = read();
		if(op == 2) printf("%lld\n", sum[1]);
		else {
			int x = read(), y = read();
			update(x, y), pw = (pw + pw) % mod;
		}
	}
}