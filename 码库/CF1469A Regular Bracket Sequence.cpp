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
const int N=105;
char str[N];
int n;
void Main(){
	scanf("%s",str+1),n=strlen(str+1);
	if(n&1)return puts("NO"),void();
	int num=0;
	for(int i=1;i<=n;++i){
		if(str[i]=='(')++num;
	}
	if(num>n/2)return puts("NO"),void();
	int ned=n/2-num,now=0;
	for(int i=1;i<=n;++i){
		if(str[i]=='?'){
			if(ned>0)++now,--ned;
			else --now;
		}else if(str[i]=='(')++now;
		else --now;
		if(now<0)return puts("NO"),void();
	}
	puts("YES");
}
signed main(){for(int T=read();T;--T)Main();}//???