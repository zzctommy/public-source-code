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
const int T=N<<2;
int n,k,a[N],MAX_A,dp[N],d[N],stk[N],top,pre[N],mxv[T];
#define lc (p<<1)
#define rc (p<<1|1)
void change(int pos,int k,int l=1,int r=n,int p=1){
	ckmax(mxv[p],k);
	if(l==r)return;
	int mid=(l+r)>>1;
	if(pos<=mid)change(pos,k,l,mid,lc);
	else change(pos,k,mid+1,r,rc);
}
int query_max(int ql,int qr,int l=1,int r=n,int p=1){
	if(ql<=l&&r<=qr)return mxv[p];
	int mid=(l+r)>>1;
	if(qr<=mid)return query_max(ql,qr,l,mid,lc);
	if(mid<ql)return query_max(ql,qr,mid+1,r,rc);
	return max(query_max(ql,qr,l,mid,lc),query_max(ql,qr,mid+1,r,rc));
}
bool check(int x){
	memset(dp,-0x3f,(n+1)<<2),dp[0]=0,memset(mxv,-0x3f,sizeof(mxv));
	for(int i=1;i<=n;++i){
		if(pre[i]||a[i]%x==0)dp[i]=dp[pre[i]];
		if(a[i]%x==0){
			if(i==1)dp[i]=1;
			else {
				ckmax(dp[i],query_max(max(1,pre[i]),i-1)+1);
				if(!pre[i])ckmax(dp[i],1);
			}
		}
		change(i,dp[i]);
	}
	return dp[n]>=k;
}
signed main(){
	n=read(),k=read();
	rep(i,1,n)ckmax(MAX_A,a[i]=read());
	for(int i=1;i<=n;++i){
		while(top&&a[stk[top]]<=a[i])--top;
		pre[i]=stk[top],stk[++top]=i;
	}
	for(int i=1;i*i<=MAX_A;++i){
		if(MAX_A%i)continue;
		d[++d[0]]=i;
		if(i*i!=MAX_A)d[++d[0]]=MAX_A/i;
	}
	sort(d+1,d+d[0]+1,greater<int>());
	for(int i=1;i<=d[0];++i)if(check(d[i]))return printf("%d\n",d[i]),0;
	cout<<-1;
	return 0;
}