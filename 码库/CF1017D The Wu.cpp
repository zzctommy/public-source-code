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
inline int read2(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*2+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=500005;
int s[N];
int n,m,q,w[N],tot;
int id[5005],cnt[5005];
int mem[5000][105];
void calc(int t){
	id[t]=++tot;
	for(int i=0;i<1<<n;++i){
		if(!cnt[i])continue;
		int sum=0;
		rep(j,0,n-1)if((i>>j&1)==(t>>j&1))sum+=w[j];
		if(sum<=100)mem[t][sum]+=cnt[i];
	}
	rep(i,1,100)mem[t][i]+=mem[t][i-1];
}
signed main(){
	n=read(),m=read(),q=read();
	per(i,n-1,0)w[i]=read();
	rep(i,1,m)s[i]=read2(),++cnt[s[i]];
	rep(i,1,q){
		int t=read2(),k=read();
		if(!id[t])calc(t);
		printf("%d\n",mem[t][k]);
	}
	return 0;
}
/*
2 4 5
40 20
01
01
10
11
00 20
00 40
11 20
11 40
11 60

*/