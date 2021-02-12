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
const int N=200005;
int n,F[N],p[N],v[N],c[N][2];
LL ans;
struct node{
	int c[2],id;
	node(){c[0]=c[1]=id=0;}
	node(int c0,int c1,int id_){c[0]=c0,c[1]=c1,id=id_;}
	inline bool operator < (const node&t)const{
		if(1ll*c[0]*t.c[1]==1ll*c[1]*t.c[0])return id<t.id;
		return 1ll*c[0]*t.c[1]>1ll*c[1]*t.c[0];
	}
	inline bool operator == (const node&t)const{
		return c[0]==t.c[0]&&c[1]==t.c[1]&&id==t.id;
	}
};
set<node>s;
inline int anc(int x){return x==F[x]?x:F[x]=anc(F[x]);}
bool vis[N];
signed main(){
	n=read();
	rep(i,2,n)p[i]=read();
	rep(i,1,n)v[i]=read(),c[i][v[i]]=1,F[i]=i;
	rep(i,2,n)s.insert(node(c[i][0],c[i][1],i));
	rep(t,2,n){
		node now=*s.begin();s.erase(s.begin());
		int x=now.id,f=anc(p[x]);
		assert(!vis[x]),vis[x]=1;
		if(f!=1)s.erase(s.find(node(c[f][0],c[f][1],f)));
		ans+=1ll*c[f][1]*now.c[0];
		c[f][0]+=now.c[0],c[f][1]+=now.c[1];
		if(f!=1)s.insert(node(c[f][0],c[f][1],f));
		F[x]=f;
	}
	cout<<ans<<'\n';
}
/*
23255672
*/