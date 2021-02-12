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
const int N = 200005;
const int T = N * 44;
int n, a[N], lsh[N], len, cnt[N], ans, st[N], ed[N], tmr, dif[N];
bool flg[N], fl;
vector <int> e[N];
int rt[N], tot, ls[T], rs[T], val[T];
inline void update(int &p, int pos, int d, int l = 1, int r = n) {
	if (!p) p = ++tot;
	if (l == r) return val[p] += d, void();
	int mid = (l + r) >> 1;
	if (pos <= mid) update(ls[p], pos, d, l, mid);
	else update(rs[p], pos, d, mid + 1, r);
}
int merge(int x, int y, int l = 1, int r = n) {
	if (!x || !y) return x|y;
	int mid = (l + r) >> 1, p = ++tot;
	if (l == r) return val[p] = val[x] + val[y], p;
	ls[p] = merge(ls[x], ls[y], l, mid);
	rs[p] = merge(rs[x], rs[y], mid + 1, r);
	return p;
}
inline int query(int p, int pos, int l = 1, int r = n) {
	if (!p) return 0;
	if (l == r) return val[p];
	int mid = (l + r) >> 1;
	if (pos <= mid) return query(ls[p], pos, l, mid);
	else return query(rs[p], pos, mid + 1, r);
}
void dfs(int u, int ft) {
	update(rt[u], a[u], 1);
	st[u] = ++tmr;
	for (int v : e[u]) {
		if (v == ft) continue;
		dfs(v, u), rt[u] = merge(rt[u], rt[v]);
	}
	ed[u] = tmr;
	for (int v : e[u]) {
		if (v == ft) continue;
		if (query(rt[v], a[u])) ++dif[1], --dif[st[v]], ++dif[ed[v] + 1];
	}
	if (query(rt[u], a[u]) < cnt[a[u]]) ++dif[st[u]], --dif[ed[u] + 1];
}
int main() {
	n = read();
	rep (i, 1, n) lsh[++len] = a[i] = read();
	sort(lsh + 1, lsh + len + 1), len = unique(lsh + 1, lsh + len + 1) - lsh - 1;
	rep (i, 1, n) a[i] = lower_bound(lsh + 1, lsh + len + 1, a[i]) - lsh, ++cnt[a[i]];
	rep (i, 2, n) {
		int x = read(), y = read();
		e[x].pb(y), e[y].pb(x);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; ++i) dif[i] += dif[i - 1], ans += !dif[i];
	cout << ans << '\n';
}