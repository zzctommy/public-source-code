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

int n, m, a[107][7], inc[20], dp[2][1 << 12], ans = -1e9;

namespace Hash{
const int mod = 110017;
int val[2][11000], mxv[2][11000], nxt[11000], hed[mod];
int cnt[2], now = 0, lst = 1;

void insert(int msk, int v) {
	int t = msk % mod;
	for(int i = hed[t]; i; i = nxt[i]) {
		if(val[now][i] == msk) {
			ckmax(mxv[now][i], v);
			return;
		}
	}
	++cnt[now];
	nxt[cnt[now]] = hed[t], hed[t] = cnt[now];
	mxv[now][cnt[now]] = v, val[now][cnt[now]] = msk;
}
void clear() {
	memset(hed, 0, sizeof(hed)), now ^= 1, lst ^= 1, cnt[now] = 0;
}

}
using namespace Hash;

void solve(){
	insert(0, 0);
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= cnt[now]; ++j)
			val[now][j] <<= 2;
		for(int j = 1; j <= m; ++j) {
			clear();
			for(int k = 1; k <= cnt[lst]; ++k) {
				int msk = val[lst][k], num = mxv[lst][k];
				int b1 = (msk >> (j * 2 - 2)) % 4, b2 = (msk >> (j * 2)) % 4;
				// cout << i << ' ' << j << ':' << msk << ' ' << num << ' ' << b1 <<' ' << b2 << '\n';
				if(!b1 && !b2) {
					insert(msk, num);
					if(i < n && j < m)
						insert(msk + inc[j - 1] + inc[j] * 2, a[i][j] + num);
				} else if(!b1 && b2) {
					if(i < n) insert(msk - inc[j] * b2 + inc[j - 1] * b2, a[i][j] + num);
					if(j < m) insert(msk, a[i][j] + num);
				} else if(b1 && !b2) {
					if(j < m) insert(msk - inc[j - 1] * b1 + inc[j] * b1, a[i][j] + num);
					if(i < n) insert(msk, a[i][j] + num);
				} else if(b1 == 1 && b2 == 1) {
					int ctr = 1;
					for(int l = j + 1; l <= m; ++l) {
						if((msk >> (l * 2)) % 4 == 1) ++ctr;
						if((msk >> (l * 2)) % 4 == 2) --ctr;
						if(!ctr) {
							insert(msk - inc[j] - inc[j - 1] - inc[l], a[i][j] + num);
							break;
						}
					}
				} else if(b1 == 2 && b2 == 2) {
					int ctr = 1;
					for (int l = j - 2; l >= 0; --l) {
						if((msk >> (l * 2)) % 4 == 1) --ctr;
						if((msk >> (l * 2)) % 4 == 2) ++ctr;
						if(!ctr) {
							insert(msk - inc[j] * 2 - inc[j - 1] * 2 + inc[l], a[i][j] + num);
							break;
						}
					}
				} else if(b1 == 2 && b2 == 1) {
					insert(msk - inc[j] - inc[j - 1] * 2, a[i][j] + num);
				} else if(b1 == 1 && b2 == 2 && msk == inc[j - 1] + inc[j] * 2) {
					ckmax(ans, num + a[i][j]);
				}
			}
		}
	}
}

signed main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			a[i][j] = read();
	inc[0] = 1;
	for(int i = 1; i <= 10; ++i) inc[i] = inc[i - 1] << 2;
	solve();
	cout << ans << '\n';
}