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
int n, a[N], sum, ans[N], tot;
signed main() {
	n = read();
	for (int i = 1; i <= n; ++ i) a[i] = read();
	sort(a + 1, a + n + 1);
	for (int i = 1, j = n; i <= j; ++ i, -- j) ans[++ tot] = a[j], ans[++ tot] = a[i];
	for (int i = 2; i < n; ++ i) sum += ans[i] < ans[i - 1] && ans[i] < ans[i + 1];
	printf("%d\n", sum);
	for (int i = 1; i <= n; ++i) printf("%d ", ans[i]);
}
