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
typedef double db;
typedef long long LL;
#define N 1000005
int n, a[N], tot;
int suf[N], pre[N];
db ans[N];
struct node {
	int l, r; LL v;
	db ave(){return 1. * v / (r - l + 1);}
	node(){l = r = v = 0;}
	node(int l_, int r_, LL v_){l = l_, r = r_, v = v_;}
}p[N];
signed main(){
	n = read();
	for (int i = 1; i <= n; ++ i) a[i] = read();
	for (int i = 1; i <= n; ++ i) {
		if (a[i] > a[i - 1]) ++ tot, p[tot].l = i, p[tot].r = i, p[tot].v = a[i];
		else ++ p[tot].r, p[tot].v += a[i];
	}
	for (int i = 1; i < tot; ++ i) suf[i] = i + 1;
	for (int i = tot - 1; i >= 1; -- i) {
		while (suf[i] && p[suf[i]].ave() < p[i].ave())
			p[i] = node(p[i].l, p[suf[i]].r, p[i].v + p[suf[i]].v), suf[i] = suf[suf[i]];
	}
	for (int i = 1; i; i = suf[i]){
		db tmp = p[i].ave();
		for (int j = p[i].l; j <= p[i].r; ++ j) 
			ans[j] = tmp;
	}
	for (int i = 1; i <= n; ++ i) printf("%.9lf\n", ans[i]);
	return 0;
}