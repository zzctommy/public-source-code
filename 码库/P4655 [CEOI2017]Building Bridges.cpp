#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define mkp(x,y) make_pair(x,y)
#define fi first
#define se second
#define pb(x) push_back(x)
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define N 100005
#define M 1000005
#define C (M-5)
#define T (M<<2)
#define inf 1000000000000000000ll
int n,h[N],w[N],cnt;
LL s[N],dp[N];
int v[T];
pair<int,LL>li[N];
#define val(x,y) (1ll*li[x].fi*y+li[x].se)
#define lc (p<<1)
#define rc (p<<1|1)
void update(int id,int l=1,int r=C,int p=1){
	if(!v[p])return v[p]=id,void();
	int mid=(l+r)>>1;
	LL nol=val(id,l),nor=val(id,r),lal=val(v[p],l),lar=val(v[p],r);
	if(nol>=lal&&nor>=lar)return;
	if(nol<=lal&&nor<=lar)return v[p]=id,void();
	db inter=1.*(li[id].se-li[v[p]].se)/(li[v[p]].fi-li[id].fi);
	if(nol<=lal){
		if(inter<=mid)update(id,l,mid,lc);
		else update(v[p],mid+1,r,rc),v[p]=id;
	}else{
		if(inter>mid)update(id,mid+1,r,rc);
		else update(v[p],l,mid,lc),v[p]=id;
	}
}
LL query(int X,int l=1,int r=C,int p=1){
	LL res=inf;
	if(v[p])res=min(res,val(v[p],X));
	if(l==r)return res;
	int mid=(l+r)>>1;
	if(X<=mid)res=min(res,query(X,l,mid,lc));
	else res=min(res,query(X,mid+1,r,rc));
	return res;
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i)h[i]=read();
	for(int i=1;i<=n;++i)w[i]=read(),s[i]=s[i-1]+w[i];
	for(int i=1;i<=n;++i){
		if(i==1)dp[i]=0;
		else dp[i]=query(h[i])+1ll*h[i]*h[i]+s[i-1];
		li[++cnt]=mkp(-2*h[i],dp[i]-s[i]+1ll*h[i]*h[i]);
		update(cnt);
	}
	printf("%lld\n",dp[n]);
	return 0;
}