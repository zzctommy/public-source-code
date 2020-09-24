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
const int N = 55;
int n, m, at[N][N];
struct node {
	int x, y, id;
}a[N];
vector<pair<int,int> >ans[2]; 
inline bool cmp(const node&a, const node&b) {
	return a.x < b.x;
}
void move(int id, int i, int dx, int dy) {
	int x = a[i].x, y = a[i].y, nx = x + dx, ny = y + dy;
	if (at[nx][ny]) move(id, at[nx][ny], dx, dy);
	ans[id].pb(mkp(x, y)), ans[id].pb(mkp(nx, ny));
	swap(at[x][y], at[nx][ny]);
	a[i].x += dx, a[i].y += dy;
}
signed main() {
	n = read(), m = read();
	for (int t = 0; t < 2; ++ t) {
		memset(at, 0, sizeof(at));
		for (int i = 1; i <= m; ++ i) a[i].x = read(), a[i].y = read(), a[i].id = i;
		sort(a + 1, a + m + 1, cmp);
		for (int i = 1; i <= m; ++ i) at[a[i].x][a[i].y] = i;
		for (int i = 1; i <= m; ++ i) {
			while (a[i].x < i) move(t, i, 1, 0);
			while (a[i].x > i) move(t, i, -1, 0);
		}
		for (int i = 1; i <= m; ++ i) {
			while (a[i].y < a[i].id) move(t, i, 0, 1);
			while (a[i].y > a[i].id) move(t, i, 0, -1);
		}
		for (int i = 1; i <= m; ++ i) {
			while (a[i].x < a[i].id) move(t, i, 1, 0);
			while (a[i].x > a[i].id) move(t, i, -1, 0);
		}
	}
	printf("%d\n",(ans[0].size()+ans[1].size())/2);
	for (int i = 0; i < ans[0].size(); i += 2) printf ("%d %d %d %d\n", ans[0][i].first, ans[0][i].second, ans[0][i + 1].first, ans[0][i + 1].second);
	reverse(ans[1].begin(),ans[1].end());
	for (int i = 0; i < ans[1].size(); i += 2) printf ("%d %d %d %d\n", ans[1][i].first, ans[1][i].second, ans[1][i + 1].first, ans[1][i + 1].second);
	return 0;
}
