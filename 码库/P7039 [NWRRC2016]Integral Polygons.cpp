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
#define int long long
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N = 200005;
const int C = 1e9;
int n, x[N], y[N], s[N][2][2][2], ans, sum[N];
signed main() {
	n = read();
	for(int i = 1; i <= n; ++i) x[i] = (read() + C) & 1, y[i] = (read() + C) & 1;
	int S = 0;
	for(int i = 2; i <= n; ++i) S += x[i] * y[i - 1] + y[i] * x[i - 1];
	if((S + x[1] * y[n] + y[1] * x[n]) & 1) return puts("0"), 0;
	for(int i = 2; i <= n; ++i) {
		rep(a, 0, 1) rep(b, 0, 1) rep(c, 0, 1)
			s[i][a][b][c] = s[i - 1][a][b][c];
		int t = (x[i - 1] * y[i] + x[i] * y[i - 1]) & 1;
		sum[i] = sum[i - 1] ^ t;
		++s[i][x[i]][y[i]][sum[i]];
	}
	for(int i = 1; i <= n - 1; ++i) {
		rep(a, 0, 1) rep(b, 0, 1) rep(c, 0, 1) {
			int tmp = (x[i] * b + y[i] * a + c - sum[i] + 114514) & 1;
			if(!tmp) ans += s[n][a][b][c] - s[i][a][b][c];
		}
	}
//	rep(i, 1, n) {
//		int p = 0;
//		rep(j, i + 1, n) {
//			p += x[j - 1] * y[j] + x[j] * y[j - 1];
//			if((p + x[i] * y[j] + x[j] * y[i]) % 2 == 0) ++ans;
//		}
//	}
	cout << ans - n << '\n';
}