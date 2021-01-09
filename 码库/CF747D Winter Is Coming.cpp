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
const int N=200005;
int n,k,a[N],num,b[N],lst,tot,cnt,ano;
signed main(){
	n=read(),k=read();
	rep(i,1,n)a[i]=read()<0,num+=a[i];
	if(num>k)return puts("-1"),0;
	k-=num;
	rep(i,1,n)if(a[i]!=a[i-1])++cnt;
	rep(i,1,n)if(a[i]){
		if(lst&&a[i]!=a[i-1])b[++tot]=i-1-lst;
		lst=i;
	}
	if(!a[n])ano=n-lst;
	else ano=1919810;
	// rep(i,1,tot)cerr<<b[i]<<' ';cerr<<'\n';
	// cerr<<ano<<'\n';
	sort(b+1,b+tot+1);
	for(int i=1;i<=tot;++i)if(k>=b[i])k-=b[i],cnt-=2;else break;
	if(k>=ano&&lst)--cnt;
	printf("%d\n",cnt);
	return 0;
}