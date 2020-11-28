#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define N 100005
int n;
LL k;
struct point {
	int x, y;
}p[N];
bool cmp(const point&a, const point&b){
	return a.x != b.x ? a.x < b.x : a.y < b.y;
}
LL tr[N];
void add(int x, int d) { for (int i = x; i <= n; i += i & -i) tr[i] += d; }
LL ask(int x) { LL res = 0; for (int i = x; i > 0 ;i -= i & -i) res += tr[i]; return res; }
#define lsh(x) (lower_bound(b + 1, b + len + 1, x) - b)
LL check(int sl) {
	static LL a[N], b[N];
	static int len;
	for (int i = 1; i <= n; ++ i) b[i] = a[i] = 1ll * sl * p[i].x - p[i].y;
	sort(b + 1, b + n + 1), len = unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; ++ i) a[i] = n - lsh(a[i]) + 1;
	memset(tr, 0, sizeof(tr));
	LL res = 0;
	for (int i = 1; i <= n;) {
		int l = i, r = i;
		while (p[r + 1].x == p[l].x) ++ r;
		for (int j = l; j <= r; ++ j) res += ask(a[j]);
		for (int j = l; j <= r; ++ j) add(a[j], 1);
		i = r + 1;
	}
	return res;
}
signed main(){
	scanf("%d%lld",&n, &k);
	for (int i = 1; i <= n; ++ i) scanf("%d%d", &p[i].x, &p[i].y);
	sort(p + 1, p + n + 1, cmp);
	int l = -2e8, r = 2e8, res = -1;
	while (l <= r){
		int mid = (l + r) >> 1;
		if (check(mid) < k) r = mid - 1;//sum(slope >= mid) < k
		else res = mid, l = mid + 1;
	}
	printf("%d\n",res);
	return 0;
}
/*
4 1
-1 -1
2 1
3 3
1 4

2

4 1
1 1
2 5
3 4
4 3

5

*/