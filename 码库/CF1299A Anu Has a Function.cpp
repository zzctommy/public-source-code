#include<bits/stdc++.h>
using namespace std;
inline int read(){
	#define gc getchar()
	int x = 0, f = 1; char c = gc;
	while (!isdigit(c)) { if (c == '-') f = 0; c = gc; }
	while (isdigit(c)) x = x * 10 + c - '0', c = gc;
	#undef gc
	return f ? x : -x;
}
#define N 100005
int n, a[N], cnt[35];
signed main(){
	n = read();
	for (int i = 1; i <= n; ++ i) {
		a[i] = read();
		for (int j = 0; j < 31; ++ j) cnt[j] += a[i] >> j & 1;
	}
	for (int i = 0; i < 31; ++ i) cerr << cnt[i] << ' '; cerr << '\n';
	int pos = 114514, now = -1919810;
	for (int i = 1; i <= n; ++ i) {
		int sum = 0;
		for (int j = 0; j < 31; ++ j) if (a[i] >> j & 1 && cnt[j] <= 1) sum += 1 << j;
		if (sum > now) now = sum, pos = i;
	}
	swap(a[pos], a[1]);
	for (int i = 1; i <= n; ++ i) printf("%d ",a[i]);
	return 0;
}