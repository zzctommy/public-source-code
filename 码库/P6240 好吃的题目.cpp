#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = 0; c = getchar(); }
	while(isdigit(c)) x = x * 10 + (c ^ 48), c = getchar();
	return f ? x : -x;
}
template <class T> inline bool ckmax(T &x, T y) { return x < y ? x = y, 1 : 0;}
template <class T> inline bool ckmin(T &x, T y) { return x > y ? x = y, 1 : 0;}

const int N = 40005;
const int M = 200005;
int n, m, h[N], w[N], ans[M], bg1[N][205], bg2[N][205];
struct node {
	int l, r, t, id;
} q[M], q1[M], q2[M], q3[M];
void solve(int l, int r, int x, int y) {
	if(x > y) return;
	if(l == r) {
		for(int i = x; i <= y; ++i)
			ans[q[i].id] = h[l] <= q[i].t ? w[l] : 0;
		return;
	}
	int mid = (l + r) >> 1, t1 = 0, t2 = 0, t3 = 0, it = x;
	for(int i = x; i <= y; ++i)
		if(q[i].r <= mid) q1[++t1] = q[i];
		else if(q[i].l >= mid + 1) q2[++t2] = q[i];
		else q3[++t3] = q[i];
	for(int i = 1; i <= t1; ++i) q[it++] = q1[i];
	for(int i = 1; i <= t2; ++i) q[it++] = q2[i];
	for(int i = 1; i <= t3; ++i) q[it++] = q3[i];
	solve(l, mid, x, x + t1 - 1), solve(mid + 1, r, x + t1, x + t1 + t2 - 1);
	memset(bg1[mid + 1], 0, sizeof(bg1[mid + 1]));
	memset(bg2[mid], 0, sizeof(bg2[mid]));
	for(int i = mid; i >= l; --i) {
		for(int j = 200; j >= 0; --j){
			bg1[i][j] = bg1[i + 1][j];
			if(j >= h[i]) ckmax(bg1[i][j], bg1[i + 1][j - h[i]] + w[i]);
		}
	}
	for(int i = mid + 1; i <= r; ++i) {
		for(int j = 200; j >= 0; --j) {
			bg2[i][j] = bg2[i - 1][j];
			if(j >= h[i]) ckmax(bg2[i][j], bg2[i - 1][j - h[i]] + w[i]);
		}
	}
	for(int i = x + t1 + t2; i <= y; ++i) {
		int res = 0, t = q[i].t, ll = q[i].l, rr = q[i].r;
		for(int j = 0; j <= t; ++j)
			ckmax(res, bg1[ll][j] + bg2[rr][t - j]);
		ans[q[i].id] = res;
	}
}
signed main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) h[i] = read();
	for(int i = 1; i <= n; ++i) w[i] = read();
	for(int i = 1; i <= m; ++i)
		q[i].l = read(), q[i].r = read(), q[i].t = read(), q[i].id = i;
	solve(1, n, 1, m);
	for(int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
	return 0;
}