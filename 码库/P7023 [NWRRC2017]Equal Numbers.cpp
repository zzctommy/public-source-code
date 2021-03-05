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
const int N=1000005;
int n,a[N],cnt[N],f[N],tot,ans[N];
signed main(){
	n=read();
	rep(i,1,n)++cnt[a[i]=read()];
	int now=0;
	for(int i=1;i<N;++i)if(cnt[i])++now;
	for(int i=1;i<N;++i){
		if(!cnt[i])continue;
		for(int j=2;i*j<N;++j)
			if(cnt[i*j]){f[++tot]=cnt[i];break;}
	}
		
	sort(f+1,f+tot+1);
//	rep(i,1,tot)cout<<f[i]<<' ';cout<<'\n';
	sort(cnt+1,cnt+N);
	ans[0]=now;
	for(int i=1,j=1,t=now+1;i<N;++i){
		if(!cnt[i])continue;
		for(int k=1;k<cnt[i];++k)ans[j++]=min(t,now);
		ans[j++]=--t;
	}
//	rep(i,0,n)cerr<<ans[i]<<' ';cerr<<'\n';
	for(int i=1,j=1;i<=tot;++i){
		for(int k=1;k<f[i];++k)ckmin(ans[j++],now);
		ckmin(ans[j++],--now);
	}
	rep(i,1,n)ckmin(ans[i],ans[i-1]);
	rep(i,0,n)printf("%d ",ans[i]);
	return 0;
}
/*
6
3 6 4 8 5 10

5
1 2 4 8 16

4
1 2 3 9

*/