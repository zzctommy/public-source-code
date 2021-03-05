#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
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
const int N = 300005;
const int inf = 0x3f3f3f3f;
int n, m, cnt[N], nxt[N], ans[N], to[N], F[N];
inline int anc(int x) { while(x != F[x]) x = F[x] = F[F[x]]; return x; }
struct node {
	int x, y, op;
	node(){ x = y = op = 0; }
	node(int x_, int y_, int op_) { x = x_, y = y_, op = op_; }
} a[N << 1];
set <pair<int, int> > s;
inline bool cmp(const node &a, const node &b) {
	return a.y != b.y ? a.y > b.y : a.op > b.op;
}
signed main(){
	n=read();
	rep(i, 1, n)
		a[i].x = read(), a[i].y = read(), a[i].op = 0;
	m = read();
	rep(i, n + 1, n + m)
		a[i].x = read(), a[i].y = read(), a[i].op = i - n;
	sort(a + 1, a + n + m + 1, cmp);
	s.insert(mkp(inf, m + 1));
	rep(i, 1, n + m) {
		if(!a[i].op) {
			++cnt[s.lower_bound(mkp(a[i].x, 0))->se];
		} else {
			s.insert(mkp(a[i].x, a[i].op));
			nxt[a[i].op] = s.upper_bound(mkp(a[i].x, a[i].op))->se;
			while("fyy AKK AKK") {
				auto it = s.lower_bound(mkp(a[i].x, a[i].op));
				if(it == s.begin())break;
				--it;
				if(it->se < a[i].op) break;
				s.erase(it);
			}
		}
	}
	rep(i, 1, m) F[i] = i;
	for(int i = m; i >= 1; --i) {
		ans[i] = cnt[anc(i)];
		if(nxt[i] <= m) {
			int f = anc(nxt[i]), x = anc(i);
			cnt[f] += cnt[x], F[x] = f;
		}
	}
	for(int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
	return 0;
}