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
/*
50 49
1 1
1 2
1 3
1 4
1 5
1 6
1 7
2 1
2 2
2 3
2 4
2 5
2 6
2 7
3 1
3 2
3 3
3 4
3 5
3 6
3 7
4 1
4 2
4 3
4 4
4 5
4 6
4 7
5 1
5 2
5 3
5 4
5 5
5 6
5 7
6 1
6 2
6 3
6 4
6 5
6 6
6 7
7 1
7 2
7 3
7 4
7 5
7 6
7 7
50 50
50 49
50 48
50 47
50 46
50 45
50 44
49 50
49 49
49 48
49 47
49 46
49 45
49 44
48 50
48 49
48 48
48 47
48 46
48 45
48 44
47 50
47 49
47 48
47 47
47 46
47 45
47 44
46 50
46 49
46 48
46 47
46 46
46 45
46 44
45 50
45 49
45 48
45 47
45 46
45 45
45 44
44 50
44 49
44 48
44 47
44 46
44 45
44 44
*/