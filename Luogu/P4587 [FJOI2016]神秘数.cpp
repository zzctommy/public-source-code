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
const int T=N*32;
#define UP 1000000001
int n,a[N];
int ls[T],rs[T],sum[T],rt[N],tot;
void update(int pre,int&now,int pos,int l,int r){
	now=++tot;
	sum[now]=sum[pre]+pos,ls[now]=ls[pre],rs[now]=rs[pre];
	//cerr<<now<<' '<<pos<<' '<<sum[now]<<' '<<l<<' '<<r<<'\n';
	if(l==r)return;
	int mid=(l+r)>>1;
	if(pos<=mid)update(ls[pre],ls[now],pos,l,mid);
	else update(rs[pre],rs[now],pos,mid+1,r);
}
int query(int pre,int now,int ql,int qr,int l,int r){
	if(!now)return 0;
	//cerr<<pre<<' '<<now<<' '<<ql<<' '<<qr<<' '<<l<<' '<<r<<'\n';
	if(ql<=l&&r<=qr)return sum[now]-sum[pre];
	int mid=(l+r)>>1,res=0;
	if(ql<=mid)res+=query(ls[pre],ls[now],ql,qr,l,mid);
	if(mid<qr)res+=query(rs[pre],rs[now],ql,qr,mid+1,r);
	return res;
}
signed main(){
	n=read();
	rep(i,1,n)a[i]=read(),update(rt[i-1],rt[i],a[i],1,UP);
	for(int T=read();T;--T){
		int l=read(),r=read(),nsm=1,lsm=0;
		while("fyy AK IOI"){
			int tmp=query(rt[l-1],rt[r],lsm+1,nsm,1,UP);
			if(!tmp)break;
			//cerr<<lsm+1<<' '<<nsm<<' '<<tmp<<'\n';
			lsm=nsm,nsm+=tmp;
		}
		printf("%d\n",nsm);
	}
	return 0;
}