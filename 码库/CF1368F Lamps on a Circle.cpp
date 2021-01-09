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
const int N = 1005;
int n, a[N], len, tot, input;
bool vis[N];
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >> n;
	if (n <= 3) return cout << 0 << endl, 0;
	for (len = 1; len * len < n; ++ len);
	for (int i = 1; i <= n; ++ i) if ((i - 1) % len) a[++ tot] = i;
	while ("fyy AK IOI") {
		if (len > tot) break;
		cout << len;
		for (int i = 1; i <= len; ++ i) cout << ' ' << a[tot], vis[a[tot]] = 1, -- tot;
		cout << endl;
		cin >> input;
		for (int i = input, j = 0; j < len; i = i % n + 1, ++ j) if (vis[i]) vis[i] = 0, a[++ tot] = i;
	}
	cout << "0" << endl;
	return 0;
}
