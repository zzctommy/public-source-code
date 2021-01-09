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
const int N = 1e7 + 5;
double ans;
int n, A, B, C, a[N];
signed main() {
	scanf("%d%d%d%d%d", &n, &A, &B, &C, a + 1);
	for (int i = 2; i <= n; i++)
		a[i] = ((long long) a[i - 1] * A + B) % 100000001;
	for (int i = 1; i <= n; i++)
		a[i] = a[i] % C + 1;
	for (int i = 1; i < n; ++ i) ans += 1. * min(a[i], a[i + 1]) / (1ll * a[i] * a[i + 1]);
	ans += 1. * min(a[1], a[n]) / (1ll * a[1] * a[n]);
	printf("%.3lf\n", ans);
}