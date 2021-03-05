#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
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
const int N = 200005;
const int T = N << 2;
int n, m, a[N], ans;
LL y;
int miv[T], tag[T];
LL sum[T];
#define lc (p << 1)
#define rc (p << 1 | 1)
inline void pushup(int p) {
	miv[p] = min(miv[lc], miv[rc]);
	sum[p] = sum[lc] + sum[rc];
}
void build(int l = 1, int r = n, int p = 1) {
	if(l == r) {
		sum[p] = miv[p] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lc), build(mid + 1, r, rc);
	pushup(p);
}
inline void pushdown(int p, int l, int r) {
	if(tag[p]) {
		int mid = (l + r) >> 1;
		tag[lc] = tag[p], sum[lc] = 1ll * (mid - l + 1) * tag[p], miv[lc] = tag[p];
		tag[rc] = tag[p], sum[rc] = 1ll * (r - mid) * tag[p], miv[rc] = tag[p];
		tag[p] = 0;
	}
}
int solve1(int d, int l = 1, int r = n, int p = 1) {
	if(l == r) return l;
	int mid = (l + r) >> 1;
	pushdown(p, l, r);
	if(d >= miv[lc]) return solve1(d, l, mid, lc);
	else return solve1(d, mid + 1, r, rc);
}
void cov(int ql, int qr, int d, int l = 1, int r = n, int p = 1) {
	if(ql > qr) return;
	if(ql <= l && r <= qr) {
		miv[p] = d, sum[p] = 1ll * d * (r - l + 1), tag[p] = d;
		return;
	}
	pushdown(p, l, r);
	int mid = (l + r) >> 1;
	if(ql <= mid) cov(ql, qr, d, l, mid, lc);
	if(mid < qr) cov(ql, qr, d, mid + 1, r, rc);
	pushup(p);
}
inline LL query_sum(int ql, int qr, int l = 1, int r = n, int p = 1) {
	if(ql > qr) return 0;
	if(ql <= l && r <= qr) return sum[p];
	pushdown(p, l, r);
	int mid = (l + r) >> 1; LL res = 0;
	if(ql <= mid) res += query_sum(ql, qr, l, mid, lc);
	if(mid < qr) res += query_sum(ql, qr, mid + 1, r, rc);
	return res;
}
inline void solve(int l = 1, int r = n, int p = 1) {
	if(sum[p] <= y)return y -= sum[p], ans += r - l + 1, void();
	if(l == r) return;
	pushdown(p, l, r);
	if(miv[p] <= y) {
		int mid = (l + r) >> 1;
		if(miv[lc] <= y) solve(l, mid, lc);
		if(miv[rc] <= y) solve(mid + 1, r, rc);
	}
}
signed main() {
	n = read(), m = read();
	rep(i, 1, n) a[i] = read();
	build();
	while(m--) {
		int opt = read(), x = read(); y = read();
		if(opt == 1) cov(solve1(y), x, y);
		else y += query_sum(1, x - 1), ans = 0,
			solve(), printf("%d\n", ans - x + 1);
	}
	return 0;
}