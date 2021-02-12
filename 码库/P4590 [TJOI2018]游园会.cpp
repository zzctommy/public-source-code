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
#define mod 1000000007
inline void fmod(int &x) { x -= mod, x += x >> 31 & mod; }
int n, k, f[2][1 << 15][3], a[20], cnt[1<<15], ans[20], mem[1 << 15][3];
char str[20];
int trans(int msk, int c) {
	if (mem[msk][c]) return mem[msk][c];
	static int A[20], B[20];
	int res = 0;
	A[0] = B[0] = 0;
	for (int i = 0; i < k; ++i) A[i + 1] = A[i] + (msk >> i & 1);
	for (int i = 1; i <= k; ++i) B[i] = max(max(B[i - 1], A[i]), (c == a[i]) * (A[i - 1] + 1));
	for (int i = 0; i < k; ++i) res |= (B[i + 1] - B[i]) << i;
	return mem[msk][c] = res;
}
signed main() {
	scanf("%d%d%s",&n, &k, str + 1);
	for(int i = 1; i <= k; ++i)
		a[i] = str[i] == 'N' ? 0 : str[i] == 'O' ? 1 : 2;
	for (int i = 0; i < 1 << k; ++i) cnt[i] = cnt[i >> 1] + (i&1); 
	f[0][0][0] = 1;
	for (int i = 0, u = 0; i < n; ++i, u ^= 1) {
		memset(f[u^1], 0, sizeof(f[u^1]));
		for (int msk = 0, U = 1 << k; msk < U; ++msk) {
			for (int j = 0; j < 3; ++j) {
				if (!f[u][msk][j]) continue;
				for (int c = 0; c < 3; ++c) {
					int l = 0, nex = msk;
					if (c == 0) l = 1;
					else if (j == 1 && c == 1) l = 2;
					else if (j == 2 && c == 2) continue;
					fmod(f[u^1][trans(msk, c)][l] += f[u][msk][j]);
				}
			}
		}
	}
	for (int msk = 0, U = 1 << k; msk < U; ++msk) 
		fmod(ans[cnt[msk]] += f[n&1][msk][0]),
		fmod(ans[cnt[msk]] += f[n&1][msk][1]),
		fmod(ans[cnt[msk]] += f[n&1][msk][2]);
	for(int i=0;i <= k; ++i) printf("%d\n", ans[i]);
	return 0;
}