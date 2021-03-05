#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
typedef long long LL;
typedef long double db;
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

const int N = 100005;
int A[N], B[N], n, a[N], s[N], ans = 1e18, k;
signed main() {
	n = read(), k = read();
	rep(i, 1, n) A[i] = read();
	rep(i, 1, n) B[i] = read();
	for(int i = 1; i <= n; ++i) a[i] = A[i] - B[i];
	sort(a + 1, a + n + 1);
	for(int i = n; i >= 1; --i) a[i] -= a[1];
	for(int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i];
//	for(int i = 1; i <= n; ++i) cout << a[i] << ' '; cout << '\n';
//	for(int i = 1; i <= n; ++i) cout << s[i] << ' '; cout << '\n';
	for(int l = 1; l <= n; ++l) {
		int r = l + n - k - 1;
		if(r > n) break;
		int mid = (l + r) >> 1, t = (r - l + 1) >> 1;
		if((r - l + 1) & 1) {
			ckmin(ans, s[r] - s[mid] - a[mid] * t + a[mid] * t - (s[mid - 1] - s[l - 1]));
		} else ckmin(ans, s[r] - s[mid] - a[mid] * t + a[mid] * t - (s[mid] - s[l - 1]));
	}
	cout << ans << '\n';
	return 0;
}