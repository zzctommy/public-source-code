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
int n,m,a,b;
char S[N],T[N];
signed main(){
	scanf("%s%s",S+1,T+1);
	n=strlen(S+1),m=strlen(T+1);
	a=0,b=0;
	rep(i,1,n)if(S[i]!='0'){a=i;break;}
	rep(i,1,m)if(T[i]!='0'){b=i;break;}
	if(!a&&!b)return puts("="),0;
	if(!a&&b)return puts("<"),0;
	if(a&&!b)return puts(">"),0;
	if(n-a+1>m-b+1)return puts(">"),0;
	else if(n-a+1<m-b+1)return puts("<"),0;
	int i=a,j=b;
	while(i<=n&&j<=m){
		if(S[i]<T[j])return puts("<"),0;
		else if(S[i]>T[j])return puts(">"),0;
		++i,++j;
	}
	puts("=");
}