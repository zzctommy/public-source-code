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
const int inf=0x3f3f3f3f;
int n,a[N],nxt[N];
int lg[N],pw[20];
void init_ST(){
	lg[0]=-1;rep(i,1,n)lg[i]=lg[i>>1]+1;
	pw[0]=1;rep(i,1,19)pw[i]=pw[i-1]<<1;
}
struct ST_TABLE{
ST_TABLE(){memset(ST,0x3f,sizeof(ST));}
int ST[20][N],id[20][N];
void init(){
	rep(i,1,lg[n])rep(j,1,n-pw[i]+1){
		const int t=j+pw[i-1];
		if(ST[i-1][j]<ST[i-1][t])ST[i][j]=ST[i-1][j],id[i][j]=id[i-1][j];
		else ST[i][j]=ST[i-1][t],id[i][j]=id[i-1][t];
	}
}
int ask(int l,int r){
	if(l>r)return 0;
	const int x=lg[r-l+1],t=r-pw[x]+1;
	return ST[x][l]<ST[x][t]?id[x][l]:id[x][t];
}
}ST[3];
struct node{
	int l,r,v;
	node(){l=r=v=0;}
	node(int l_,int r_){l=l_,r=r_,v=ST[l&1].ask(l,r);}
	inline bool operator < (const node&t)const{
		return a[v]<a[t.v];
	}
};
set<node>s;
signed main(){
	n=read(),init_ST(),a[0]=inf;
	rep(i,1,n)ST[i&1].ST[0][i]=ST[2].ST[0][i]=a[i]=read(),ST[i&1].id[0][i]=ST[2].id[0][i]=i;
	ST[0].init(),ST[1].init(),ST[2].init();
	s.insert(node(1,n));
	rep(i,1,n>>1){
		node now=*s.begin();s.erase(s.begin());
		int l=now.l,r=now.r,id1=now.v,id2=ST[(l&1)^1].ask(id1+1,r);
		printf("%d %d ",a[id1],a[id2]);
		if(l<=id1-1)s.insert(node(l,id1-1));
		if(id1+1<=id2-1)s.insert(node(id1+1,id2-1));
		if(id2+1<=r)s.insert(node(id2+1,r));
	}
	return 0;
}