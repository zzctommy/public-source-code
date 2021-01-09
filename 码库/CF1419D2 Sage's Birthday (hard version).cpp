#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100005;
int n, a[N];
vector<int>t;
bool check(int m) {
	int i = 1, j = n - m, res = 0;
	for (int k = 1; k <= n; ++ k) t[k] = 0;
	for (int k = 1; k <= m; ++ k) t[2 * k] = a[i ++];
//	for (int k = 1; k <= n; ++ k) printf("%d ", t[k]);puts("");
	for (int k = 1; k <= m + 1; ++ k) t[2 * k - 1] = a[j ++];
//	for (int k = 1; k <= n; ++ k) printf("%d ", t[k]);puts("");
	for (int k = 2 * m + 2; k <= n; ++ k) t[k] = a[i ++];
//	for (int k = 1; k <= n; ++ k) printf("%d ", t[k]);puts("");
	for (int k = 2; k < n; ++ k)res += t[k] < t[k - 1] && t[k] < t[k + 1];
	return res >= m;
}
signed main() {
	n = read(), t.resize(n+1);
	for (int i = 1; i <= n; ++ i) a[i] = read();
	sort(a + 1, a + n + 1);
	int l = 0, r = (n - 1) >> 1, res = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid))l = mid + 1, res = mid;
		else r = mid - 1;
	}
	printf("%d\n", res), check(res);
	for (int i = 1; i <= n; ++i) printf("%d ", t[i]);
	return 0;
}
