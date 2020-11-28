#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}

#define N 1000005
#define T (N<<1)

int n, Q, m, tag[T];
char str[N];
int trans[T][26], link[T], mxlen[T], tot = 1;
int cnt[T], q[T], t[N];

int extend(int c,int lst){
	int p = lst, np = ++ tot; mxlen[np] = mxlen[p] + 1;
	for (;p && !trans[p][c]; p = link[p]) trans[p][c] = np;
	if (!p) link[np] = 1;
	else {
		int q = trans[p][c];
		if(mxlen[p] + 1 == mxlen[q]) link[np] = q;
		else{
			int nq = ++ tot; mxlen[nq] = mxlen[p] + 1;
			for(int i = 0; i < 26; ++ i) trans[nq][i] = trans[q][i];
			link[nq] = link[q], link[q] = link[np] = nq;
			for(; p && trans[p][c] == q; p = link[p]) trans[p][c] = nq;
		}
	}
	return ++cnt[np], np;
}

signed main(){
	scanf("%s%d", str, &Q), n = strlen(str);
	for (int i = 0, lst = 1; i < n; ++ i) lst = extend(str[i] - 'a', lst);
	for (int i = 1; i <= tot; ++ i) ++ t[mxlen[i]];
	for (int i = 1; i <= n; ++ i) t[i] += t[i - 1];
	for (int i = 1; i <= tot; ++ i) q[t[mxlen[i]] -- ] = i;
	for (int i = tot; i >= 1; -- i) cnt[link[q[i]]] += cnt[q[i]];
	for (int t = 1; t <= Q; ++ t) {
		static char S[T];
		scanf("%s", S), m = strlen(S);
		for (int i = 0; i < m; ++ i) S[i + m] = S[i];
		int p = 1, now = 0, res = 0;
		for (int i = 0; i < m << 1; ++ i) {
			int c = S[i] - 'a';
			if (trans[p][c]) p = trans[p][c], ++ now;
			else {
				for (; p && ! trans[p][c]; p = link[p]);
				if (!p) now = 0, p = 1;
				else now = mxlen[p] + 1, p = trans[p][c];
			}
			if (now >= m){
				while (mxlen[link[p]] >= m) now = mxlen[link[p]], p = link[p];
				if (tag[p] != t) res += cnt[p], tag[p] = t;
			} 
		}
		printf("%d\n", res);
	}
}
/*
baabaabaaa
5
a
ba
baa
aabaa
aaba

*/