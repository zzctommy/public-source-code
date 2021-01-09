#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef long long LL;
typedef double db;
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N = 200005;
int n, a[N], dp[N][3][2][2];//pos=i,2'-'+'+',+1-0,continueop
void ckmax(int&x, int y){if (x < y) x = y; }
signed main() {
	n = read();
	for (int i = 1; i <= n; ++ i) a[i] = read();
	if (n == 1) return printf("%lld\n", a[1]), 0;
	memset(dp, -0x3f, sizeof(dp));
	dp[1][2][0][0] = - a[1], dp[1][1][1][0] = a[1];
	for (int i = 1; i < n; ++ i) {
		for (int j = 0; j < 3; ++ j) {
			ckmax(dp[i + 1][(j + 1) % 3][1][1], max(dp[i][j][1][0], max(dp[i][j][1][1], dp[i][j][0][1])) + a[i + 1]);
			ckmax(dp[i + 1][(j + 1) % 3][1][0], dp[i][j][0][0] + a[i + 1]);
			ckmax(dp[i + 1][(j + 2) % 3][0][1], max(dp[i][j][0][0], max(dp[i][j][0][1], dp[i][j][1][1])) - a[i + 1]);
			ckmax(dp[i + 1][(j + 2) % 3][0][0], dp[i][j][1][0] - a[i + 1]);
		}
	}
	printf("%lld\n",max(dp[n][1][0][1], dp[n][1][1][1]));
	return 0;
}