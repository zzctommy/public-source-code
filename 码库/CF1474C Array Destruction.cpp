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
const int M=1000005;
const int N=1005;
int a[N<<1],n,cnt[M];
bool check(int x){
	rep(i,1,n<<1)++cnt[a[i]];
	int now=a[n<<1]+x,num=0;
	per(i,n<<1,1){
		if(cnt[a[i]]){
			if(now<=a[i]||!cnt[now-a[i]]){
				rep(j,1,n<<1)cnt[a[j]]=0;
				return 0;
			}
			--cnt[now-a[i]],--cnt[a[i]],now=max(a[i],now-a[i]),++num;
		}
	}
	rep(i,1,n<<1)cnt[a[i]]=0;
	return num==n;
}
void Main(){
	n=read();
	rep(i,1,n<<1)a[i]=read();
	sort(a+1,a+n*2+1);
	for(int i=1;i<n*2;++i)if(check(a[i])){
		rep(j,1,n<<1)++cnt[a[j]];
		int now=a[n*2]+a[i];
		printf("YES\n%d\n",now);
		per(j,n<<1,1){
			if(cnt[a[j]])printf("%d %d\n",a[j],now-a[j]),--cnt[now-a[j]],--cnt[a[j]],now=max(a[j],now-a[j]);
		}
		rep(j,1,n<<1)cnt[a[j]]=0;
		return;
	}
	rep(i,1,n<<1)cnt[a[i]]=0;
	puts("NO");
}
signed main(){for(int T=read();T;--T)Main();}
/*
4
2
3 5 1 2
3
1 1 8 8 64 64
2
1 1 2 4
5
1 2 3 4 5 6 7 14 3 11

*/