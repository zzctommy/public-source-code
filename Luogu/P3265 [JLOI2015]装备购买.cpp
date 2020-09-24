#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double ldb;
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
const int N = 505;
const ldb eps = 1e-7;
int n, m, ans[2], d[N];
struct node {
	ldb p[N]; int val;
	inline bool operator<(const node&rhs)const{return val < rhs.val;}
}a[N];
signed main(){
	n = read(), m = read();
	for (int i = 1; i <= n; ++ i)
		for(int j = 1; j <= m; ++ j) a[i].p[j] = read();
	for (int i = 1; i <= n; ++ i) a[i].val = read();
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n ; ++ i) {
		for(int j = 1; j <= m ; ++ j) {
			if (fabs(a[i].p[j]) > eps) {
				if (!d[j]) {
					d[j] = i, ++ ans[0], ans[1] += a[i].val;
					break;
				} else {
					ldb div = a[i].p[j] / a[d[j]].p[j];
					for (int k = j; k <= m; ++ k) a[i].p[k] -= a[d[j]].p[k] * div;
				}
			}
		}
	}
	printf("%d %d\n", ans[0], ans[1]);
}
