#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
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
const int N=200005;
multiset<pair<int,int> ,greater<pair<int,int> > >s;
int n,m,tot,ans;
bool del[N];
struct node{
	int op,x,r,id;
}a[N<<1];
inline bool cmp(const node&a,const node&b){
	return a.x==b.x?a.op>b.op:a.x<b.x;
}
signed main(){
	n=read(),m=read();
	if(m>=n)return puts("0"),0;
	rep(i,1,n)
		a[++tot].op=1,a[tot].x=read(),
		a[++tot].op=0,a[tot].x=a[tot-1].r=read(),
		a[tot-1].id=a[tot].id=i;
	sort(a+1,a+tot+1,cmp);
	int now=0;
	for(int i=1;i<=tot;++i){
		int j=i;
		while(j<tot&&a[j+1].x==a[i].x)++j;
		rep(k,i,j){
			if(del[a[k].id])continue;
			if(a[k].op)s.insert(mkp(a[k].r,a[k].id)),++now;
			else s.erase(s.find(mkp(a[k].x,a[k].id))),--now;
		}
		while(now>m){
			--now,++ans;
			pair<int,int>t=*s.begin();
			s.erase(s.begin());
			del[t.se]=1;
		}
		i=j;
	}
	cout<<ans<<'\n';
}