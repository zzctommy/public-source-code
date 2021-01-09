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
const int N = 100005;
const int S = 250;
const int B = N / S + 3;
int n, m, a[N], L[B], R[B], num, bel[N], ans[N];
int ri[N],le[N];
struct QUE{
	int id, l, r;
	QUE(){ id = l = r = 0; }
	inline bool operator < (const QUE & t) const { return bel[l] != bel[t.l] ? l < t.l : r < t.r; }
}q[N];
void brute(int l, int r, int id){
	static int col[N], lst[N], inited = 0;
	if (!inited) memset(col, 0, sizeof(col)), inited = 1;
	int res = 0;
	for (int i = l; i <= r; ++ i)
		if (col[a[i]] != id) col[a[i]] = id, lst[a[i]] = i;
		else ckmax(res, i - lst[a[i]]);
	ans[id]=res;
}
signed main(){
	n = read() + 1, m = read(), num = (n -1) / S + 1;
	rep (i, 2, n) a[i] = read() + a[i-1];
	rep (i, 1, n) a[i] += n + 1;
	rep (i, 1, num) L[i] = R[i - 1] + 1, R[i] = i * S; R[num] = n;
	rep (i, 1, num) rep(j, L[i], R[i]) bel[j] = i;
	rep (i, 1, m) q[i].l = read(), q[i].r = read() + 1, q[i].id = i;
	sort(q + 1, q +  m + 1);
	// rep (i, 1, n) cerr << a[i] << ' '; cerr << '\n';
	for (int i = 1, j = 1; i <= num; ++i){
		int r = R[i], res = 0;
		static int lst[N];
		fill(le, le + (n << 1) + 1, n), fill(ri, ri + (n << 1) + 1, 0);
		for (; bel[q[j].l] == i; ++j){
			if (bel[q[j].l] == bel[q[j].r]) {brute(q[j].l, q[j].r, q[j].id); continue;}
			while (r < q[j].r) ++r, ckmin(le[a[r]], r), ckmax(ri[a[r]], r), ckmax(res, r - le[a[r]]);
			int tmp = res;
			for (int k = q[j].l; k <= R[i]; ++ k) lst[a[k]] = 0;
			for (int k = R[i]; k >= q[j].l; -- k) ckmax(lst[a[k]], k), ckmax(tmp, max(ri[a[k]], lst[a[k]]) - k);
			ans[q[j].id] = tmp;
		}
	}
	rep (i, 1, m) printf("%d\n", ans[i]);
	return 0;
}
/*
20 1
1 -1 1 -1 -1 -1 1 -1 1 1 1 1 -1 -1 -1 -1 -1 1 -1 1 
7 12

*/