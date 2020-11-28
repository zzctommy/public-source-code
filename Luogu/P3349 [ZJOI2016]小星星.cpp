#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch))
	{
		if (ch == '-')
			f = 0;
		ch = getchar();
	}
	while (isdigit(ch))
		x = x * 10 + ch - '0', ch = getchar();
	return f ? x : -x;
}
typedef long long LL;
#define N 17
int n, m;
LL dp[N][N][1 << N], ans, A[N][1 << N], sum[1 << N];
struct Graph
{
#define M (N * N)
	int head[N], nxt[M], to[M], ecnt;
	void addedge(int u, int v) { nxt[++ecnt] = head[u], to[ecnt] = v, head[u] = ecnt; }
#undef M
} T, G;
void OR(LL *a, int op)
{
	for (int i = 1; i < 1 << n; i <<= 1)
		for (int j = 0; j < 1 << n; j += i << 1)
			for (int k = 0; k < i; ++k)
				a[i + j + k] += a[j + k] * op;
}
void dfs(int u, int ft)
{
	memcpy(dp[u], A, sizeof(A));
	for (int o = T.head[u]; o; o = T.nxt[o])
	{
		int v = T.to[o];
		if (v == ft)
			continue;
		dfs(v, u);
		for (int x = 0; x < n; ++x)
		{
			memset(sum, 0, sizeof(sum));
			for (int t = G.head[x]; t; t = G.nxt[t])
			{
				int y = G.to[t];
				for (int i = 0; i < 1 << n; ++i)
					sum[i] += dp[v][y][i];
			}
			for (int i = 0; i < 1 << n; ++i)
				dp[u][x][i] *= sum[i];
		}
	}
}
signed main()
{
	n = read(), m = read();
	for (int i = 0; i < n; ++i)
		A[i][1 << i] = 1, OR(A[i], 1);
	for (int i = 1; i <= m; ++i)
	{
		int x = read() - 1, y = read() - 1;
		G.addedge(x, y), G.addedge(y, x);
	}
	for (int i = 1; i < n; ++i)
	{
		int x = read() - 1, y = read() - 1;
		T.addedge(x, y), T.addedge(y, x);
	}
	dfs(0, -1);
	for (int i = 0; i < n; ++i)
		OR(dp[0][i], -1), ans += dp[0][i][(1 << n) - 1];
	printf("%lld\n", ans);
	return 0;
}