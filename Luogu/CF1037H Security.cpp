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
int n, m;
char str[N];
namespace seg{

#define T ((N << 1) * 23)
int val[T], ls[T], rs[T], tot;
void update(int&p, int pos, int k, int l = 1, int r = n) {
	if (!p) p = ++ tot;
	if (l == r) return val[p] += k, void();
	int mid = (l + r) >> 1;
	if (pos <= mid) update(ls[p], pos, k, l, mid);
	else update(rs[p], pos, k, mid + 1, r);
	val[p] = val[ls[p]] + val[rs[p]];
}
int merge(int x, int y, int l = 1, int r = n) {
	if (!x || !y) return x | y;
	if (l == r) return val[x] += val[y], x;
	int mid = (l + r) >> 1, p = ++ tot;
	ls[p] = merge(ls[x], ls[y], l, mid);
	rs[p] = merge(rs[x], rs[y], mid + 1, r);
	return val[p] = val[ls[p]] + val[rs[p]], p;
}
int query(int p, int ql, int qr, int l = 1, int r = n) {
	if (!p) return 0;
	if (ql <= l && r <= qr) return val[p];
	int mid = (l + r) >> 1;
	if (ql <= mid && query(ls[p], ql, qr, l, mid)) return 1;
	if (mid < qr && query(rs[p], ql, qr, mid + 1, r)) return 1;
	return 0;  
}
#undef T

}
namespace sam{


#define S (N<<1)
int q[S], t[S], rt[S];
int mxlen[S], tot = 1, trans[S][26], to[N], link[S];
int extend(int c, int lst, int id) {
	int p = lst, np = ++ tot; mxlen[np] = mxlen[p] + 1;
	for (; p && !trans[p][c]; p = link[p]) trans[p][c] = np;
	if (!p) link[np] = 1;
	else{
		int q = trans[p][c];
		if (mxlen[p] + 1 == mxlen[q]) link[np] = q;
		else {
			int nq = ++ tot; mxlen[nq] = mxlen[p] + 1;
			for (int i = 0; i < 26; ++ i) trans[nq][i] = trans[q][i];
			link[nq] = link[q], link[q] = link[np] = nq;
			for (; p && trans[p][c] == q; p = link[p]) trans[p][c] = nq;
		}
	}
	return seg::update(rt[np], id, 1), np;
}
void insert(char*str, int n) {
	for (int i = 1, lst = 1; i <= n; ++ i) to[i] = lst = extend(str[i] - 'a', lst, i);
}
void work() {
	for (int i = 1; i <= tot; ++ i) ++ t[mxlen[i]];
	for (int i = 1; i <= n; ++ i) t[i] += t[i - 1];
	for (int i = 1; i <= tot; ++ i) q[t[mxlen[i]] --] = i;
	for (int i = tot; i > 1; -- i) rt[link[q[i]]] = seg::merge(rt[link[q[i]]], rt[q[i]]);
	// for(int i=1;i<=tot;++i)cerr<<link[i] << ' ' <<i <<'\n';
	// for(int i=0;i<26;++i)cerr<<trans[5][i]<<' ';cerr<<'\n';
}

#undef S

}
signed main() {
	scanf("%s", str + 1), n = strlen(str + 1), sam::insert(str, n), sam::work();
	for (m = read(); m ; -- m) {
		static char s[N];
		static int l, r, tmp[N], len;
		scanf("%d%d%s",&l, &r, s + 1), len = strlen(s + 1);
		int u = 1, i = 1, id = -1;
		for(;;++i) {
			tmp[i] = -1;
			for (int j = i > len ? 0 : s[i] - 'a' + 1; j < 26; ++ j){
				// if(j < 4)cerr << u << ' ' << j << ' ' << sam::trans[u][j] << '\n';
				if (seg::query(sam::rt[sam::trans[u][j]], l + i - 1, r)) { tmp[i] = j; break; }
			}
				
			u = sam::trans[u][s[i] - 'a'];
			if (!u || i > len || !seg::query(sam::rt[u], l + i - 1, r)) break;
			// if (!seg::query(sam::rt[u], l + i - 1, r)) break;
		}
		for (; i >= 1; -- i) if (~tmp[i]) { id = i; break; }
		if (!~id) puts("-1");
		else{
			for (int i = 1; i < id; ++ i)putchar(s[i]);
			putchar('a' + tmp[id]), puts("");
		}
	}
	return 0;
}
/*
baa
5
1 2 ba
2 3 a
1 2 b
2 3 aa
1 3 b

*/