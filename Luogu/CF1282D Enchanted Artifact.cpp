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
string ans;
int n, na, nb;
signed main() {
	int t;
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	for (int i = 1; i <= 300; ++ i) cout << 'a'; cout << endl;
	cin >> t; if (! t) return 0; na = 300 - t; 
	for (int i = 1; i <= 300; ++ i) cout << 'b'; cout << endl;
	cin >> t; if (! t) return 0; nb = 300 - t;
	n = na + nb;
	for (int i = 1; i < n; ++ i) {
		cout << ans << 'a';
		for (int j = 1; j <= nb; ++j) cout << 'b'; cout << endl;
		cin >> t;
		if (! t) return 0;
		if (t != n - i - nb) ans += 'b', -- nb;
		else ans += 'a', -- na; 
	}
	if (na) ans += 'a';
	if (nb) ans += 'b';
	cout << ans << endl;
}
