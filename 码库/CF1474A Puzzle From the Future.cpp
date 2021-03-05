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
int n;
char a[N],b[N];
void Main(){
	scanf("%d%s",&n,b+1);
	a[0]='0';
	for(int i=1;i<=n;++i){
		if(b[i]=='0'){
			if(a[i-1]+b[i-1]-'0'!='1')a[i]='1';
			else a[i]='0';
		}else{
			if(a[i-1]+b[i-1]-'0'!='2')a[i]='1';
			else a[i]='0';
		}
	}
	for(int i=1;i<=n;++i)printf("%c",a[i]);
	puts("");
}
signed main(){for(int T=read();T;--T)Main();}
/*
5
1
0
3
011
3
110
6
111000
6
001011

*/