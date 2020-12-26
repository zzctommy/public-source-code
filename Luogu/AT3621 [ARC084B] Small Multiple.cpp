#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=100005;
int k;
bool vis[N];
int bfs(){
	deque<pair<int,int> >q;
	q.push_back(mkp(1,1));
	while("fyy yyds"){
		pair<int,int>now=q.front();q.pop_front();
		int u=now.se;
		if(!u)return now.fi;
		if(vis[u])continue;
		vis[u]=1;
		q.push_front(mkp(now.fi,u*10%k));
		q.push_back(mkp(now.fi+1,u+1>=k?0:u+1));
	}
}
signed main(){
	k=read();
	printf("%d\n",bfs());
}