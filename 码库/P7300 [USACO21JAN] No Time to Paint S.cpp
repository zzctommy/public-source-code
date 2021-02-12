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
int n,q,a[N],pre[26][N],suf[26][N];
char str[N];
signed main(){
	scanf("%d%d%s",&n,&q,str+1);
	rep(i,1,n)a[i]=str[i]-'A';
	rep(i,0,25){
		int now=0,flg=1;
		rep(j,1,n){
			if(a[j]==i)now+=flg,flg=0;
			else if(a[j]<i)flg=1;
			pre[i][j]=now;
		}
	}
	rep(i,0,25){
		int now=0,flg=1;
		per(j,n,1){
			if(a[j]==i)now+=flg,flg=0;
			else if(a[j]<i)flg=1;
			suf[i][j]=now;
		}
	}
	/*
	rep(i,0,3){
		rep(j,1,n)cerr<<pre[i][j]<<' ';cerr<<'\n';
	}
	rep(i,0,3){
		rep(j,1,n)cerr<<suf[i][j]<<' ';cerr<<'\n';
	}
	*/
	while(q--){
		int res=0,x=read(),y=read();
		rep(i,0,25)res+=pre[i][x-1]+suf[i][y+1];
		printf("%d\n",res);
	}
	return 0;
}