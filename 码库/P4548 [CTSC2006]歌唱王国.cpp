#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef long double db;
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
#define mod 10000
void fmod(int&x){x-=mod,x+=x>>31&mod;}
int n,m,p[N],a[N],ans;
bool A[N];
void print(int n){
	int d[5];d[0]=0;
	for(;n;n/=10)d[++d[0]]=n%10;
	while(d[0]<4)d[++d[0]]=0;
	while(d[0])printf("%c",'0'+d[d[0]--]);
	puts("");
}
signed main(){
	n=read();
	for(int T=read();T;--T){
		m=read(),ans=0;
		rep(i,1,m)a[i]=read(),A[i]=0;
		p[1]=0;
		int j=0;
		for(int i=2;i<=m;++i){
			while(j&&a[j+1]!=a[i])j=p[j];
			if(a[j+1]==a[i])++j;
			p[i]=j;
		}
		j=m;
		while(j)A[j]=1,j=p[j];
		for(int i=1,j=n;i<=m;++i,j=1ll*j*n%mod)if(A[i])fmod(ans+=j);
		print(ans);
	}
}