#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define mkp make_pair
#define pb push_back
#define fi first
#define se second
#define rep(i, x, y) for (int i = x, i##end = y; i <= i##end; ++i)
#define per(i, x, y) for (int i = x, i##end = y; i >= i##end; --i)
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = 0; ch = getchar(); }
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return f ? x : -x;
}
const int N = 100005;
int n, m, dfn[N], tmr, dep[N], bz[20][N], rev[N];
LL now, di[N];
bool used[N];
set<int>S;
vector<pair<int, int> >e[N];
void dfs(int u, int ft) {
	rev[dfn[u] = ++tmr] = u, dep[u] = dep[bz[0][u] = ft] + 1;
	for (int i = 1; 1 << i <= dep[u]; ++i)
		bz[i][u] = bz[i - 1][bz[i - 1][u]];
	for (auto it = e[u].begin(); it != e[u].end(); ++it) {
		int v = it->se, w = it->fi;
		if (v == ft) continue;
		di[v] = di[u] + w, dfs(v, u);
	}
}
int LCA(int x, int y) {
	if (dep[x] < dep[y]) x ^= y ^= x ^= y;
	for (int i = 19, dif = dep[x] - dep[y]; i >= 0; --i)
		if (dif >> i & 1) x = bz[i][x];
	if (x == y) return x;
	for (int i = 19; i >= 0; --i)
		if (bz[i][x] != bz[i][y]) x = bz[i][x], y = bz[i][y];
	return bz[0][x];
}
LL dis(int x, int y) { return di[x] + di[y] - (di[LCA(x, y)] * 2); }
void add(int u) {
	if (S.size() == 0) return S.insert(dfn[u]), void();
	auto _s = S.upper_bound(dfn[u]), _p = _s;
	--_p;
	int pre = rev[_s == S.begin() ? *S.rbegin() : *_p];
	int suf = rev[_s == S.end() ? *S.begin() : *_s];
	now += dis(pre, u) + dis(suf, u) - dis(pre, suf);
	S.insert(dfn[u]);
}

void del(int u) {
	if (S.size() == 1) return S.erase(dfn[u]), void();
	auto _s = S.upper_bound(dfn[u]), _p = _s;
	--_p;
	int pre = rev[_p == S.begin() ? *S.rbegin() : *(--_p)];
	int suf = rev[_s == S.end() ? *S.begin() : *_s];
	now -= dis(pre, u) + dis(suf, u) - dis(pre, suf);
	S.erase(dfn[u]);
}
signed main(){
	n = read(), m = read();
	for (int i = 1; i < n; ++i) {
		int x = read(), y = read(), z = read();
		e[x].pb(mkp(z, y)), e[y].pb(mkp(z, x));
	}
	dfs(1, 0);
	while (m--) {
		int x = read();
		if (used[x]) del(x);
		else add(x);
		used[x] ^= 1;
		printf("%lld\n", now);
	}
	return 0;
}