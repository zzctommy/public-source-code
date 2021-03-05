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
const int N = 50005;
const int Q = 100005;
vector <pair<int,int> > que[N], upd[N];
int n, q, ans[Q];
char str[N];
namespace mgt{

const int T = N * 40;
int tot, ls[T], rs[T], le[T], ri[T];
void pushup(int p){
	if(ls[p]) le[p] = le[ls[p]];
	else le[p] = le[rs[p]];
	if(rs[p]) ri[p] = ri[rs[p]];
	else ri[p] = ri[ls[p]];
}
void addupd(int p, int len) {
	if (!ls[p] || !rs[p] || !len) return;
	upd[le[rs[p]]].pb(mkp(ri[ls[p]], len));
}
void update(int &p, int pos, int l = 1, int r = n) {
	if(!p) p = ++tot;
	if(l == r) return le[p] = ri[p] = pos, void();
	int mid = (l + r) >> 1;
	if(pos <= mid) update(ls[p], pos, l, mid);
	else update(rs[p], pos, mid + 1, r);
	pushup(p);
}
int merge(int x, int y, int len, int l = 1, int r = n) {
	if (!x || !y) return x | y;
	int mid = (l + r) >> 1, p = ++tot;
	if (l == r) return le[p] = ri[p] = l, p;
	ls[p] = merge(ls[x], ls[y], len, l, mid);
	rs[p] = merge(rs[x], rs[y], len, mid + 1, r);
	return pushup(p), addupd(p, len), p;
}
void print(int p, int l = 1, int r = n) {
	if (!p) return;
	if (l == r) return cout << l << ' ', void();
	int mid = (l + r) >> 1;
	print(ls[p], l, mid), print(rs[p], mid + 1, r);
}

}
namespace SAM{

const int M = N << 1;
int tot = 1, trans[M][26], link[M], mxlen[M], rt[M];
int q[M], t[N];
inline int extend(int c, int lst, int id) {
	int p = lst, np = ++tot; mxlen[np] = mxlen[p] + 1;
	for(; p && !trans[p][c]; p = link[p]) trans[p][c] = np;
	if(!p) link[np] = 1;
	else {
		int q = trans[p][c];
		if (mxlen[q] == mxlen[p] + 1) link[np] = q;
		else {
			int nq = ++tot; mxlen[nq] = mxlen[p] + 1;
			for(int i = 0; i < 26; ++i) trans[nq][i] = trans[q][i];
			link[nq] = link[q], link[np] = link[q] = nq;
			for(; p && trans[p][c] == q; p = link[p]) trans[p][c] = nq;
		}
	}
	mgt::update(rt[np], id);
	return np;
}
void work() {
	for(int i = 1; i <= tot; ++i) ++t[mxlen[i]];
	for(int i = 1; i <= n; ++i) t[i] += t[i - 1];
	for(int i = 1; i <= tot; ++i) q[t[mxlen[i]]--] = i;
	for(int i = tot; i >= 2; --i) {
		int u = q[i], f = link[u];
		rt[f] = mgt::merge(rt[f], rt[u], mxlen[f]);
	}
//	for(int i = 1; i <= tot; ++i) {
//		cout << i << ":";
//		mgt::print(rt[i]);
//		puts("");
//	}
}

}

namespace sgt {

const int T = N << 2;
int val[T];
#define lc (p << 1)
#define rc (p << 1 | 1)
void change(int pos, int d, int l = 1, int r = n, int p = 1) {
	ckmax(val[p], d);
	if (l == r) return;
	int mid = (l + r) >> 1;
	if(pos <= mid) change(pos, d, l, mid, lc);
	else change(pos, d, mid + 1, r, rc);
}
int query(int ql, int qr, int l = 1, int r = n, int p = 1) {
	if (ql <= l && r <= qr) return val[p];
	int mid = (l + r) >> 1, res = 0;
	if (ql <= mid) ckmax(res, query(ql, qr, l, mid, lc));
	if (mid < qr) ckmax(res, query(ql, qr, mid + 1, r, rc));
	return res;
}

}

signed main() {
	scanf("%d%d%s", &n, &q, str + 1);
	for(int i = 1; i <= q; ++i) {
		int l = read(), r = read();
		que[r].pb(mkp(l, i));
	}
	for(int i = 1, lst = 1; i <= n; ++i)
		lst = SAM::extend(str[i] - 'a', lst, i);
	SAM::work();
	for(int i = 1; i <= n; ++i) {
		for(pair <int,int> j : upd[i]) {
//			cout << "upd:" << i << ' ' << j.fi << ' ' << j.se << endl;
			sgt::change(j.fi, j.se);
		}
		for(pair <int,int> j : que[i]) {
			int l = 1, r = i - j.fi, res = 0;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (sgt::query(j.fi + mid - 1, i) >= mid) res = mid, l = mid + 1;
				else r = mid - 1;
			}
			ans[j.se] = res;
		}
	}
	for(int i = 1; i <= q; ++i) printf("%d\n", ans[i]);
	return 0;
}