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
int a[N],n,cnt[4],b[N];
int change(int x){
	int res=0;
	while(!(x&1))x>>=1,++res;
	return ckmin(res,2),res;
}
signed main(){
	n=read();
	rep(i,1,n)++cnt[a[i]=change(read())];
	if(cnt[0]){
		if(cnt[1]){
			if(!cnt[2])return puts("No"),0;
			--cnt[2];
		}
		puts(cnt[2]+1>=cnt[0]?"Yes":"No");
	}else{
		if(!cnt[2]&&cnt[1]==1)puts("No");
		else puts("Yes");
	}
	return 0;
}