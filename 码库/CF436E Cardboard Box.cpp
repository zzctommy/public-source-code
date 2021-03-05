#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0, f = 1; char c = getchar();
	while (!isdigit(c)) { if (c == '-') f = 0; c = getchar();}
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	return f ? x : -x;
}
#define fi first
#define se second
#define N 600005
#define inf 2000000009
int n, a[N], b[N], ans[N], w;
long long sum;
struct node {
	int v, id;
	node(){v = id = -1;}
	node(int v_, int i_){v = v_, id = i_;}
	inline bool operator < (const node&t)const{return v > t.v;}
};
priority_queue<node>pq[2];
bool vis[N];
signed main() {
	n = read(), w = read();
	for (int i = 1; i <= n; ++ i) {
		a[i] = read(), a[i + n] = read();
		pq[0].push(node(a[i], i)), pq[1].push(node(a[i + n], i));
		a[i + n] -= a[i];
	}
	for (int i = 1; i <= w; ++ i) {
		while (!pq[0].empty() && vis[pq[0].top().id]) pq[0].pop();
		while (!pq[1].empty() && vis[pq[1].top().id]) pq[1].pop();
		int t = pq[0].top().id; pq[0].pop();
		while (!pq[0].empty() && vis[pq[0].top().id]) pq[0].pop();
		if (i < w && !pq[1].empty() && a[t] + pq[0].top().v >= pq[1].top().v) pq[0].push(node(a[t], t)), t = pq[1].top().id, pq[1].pop();
		if (t <= n) pq[0].push(node(a[t + n], t + n));
		sum += a[t], vis[t] = 1, ++ans[(t - 1) % n + 1];
	}
	printf("%lld\n", sum);
	for (int i = 1; i <= n; ++ i) printf("%d", ans[i]);
	puts("");
}