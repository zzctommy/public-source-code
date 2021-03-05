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
int cnt[N],n,a[N],k,len,L,R;
signed main(){
	n=read(),k=read();
	rep(i,1,n)a[i]=read();
	int l=1,r=0,now=0;
	while(l<=n){
		while(r+1<=n){
			if(cnt[a[r+1]]||now<k){
				if(cnt[a[r+1]]==0)++now;
				++cnt[a[r+1]],++r;
			}
			else break;
		}
		if(ckmax(len,r-l+1))L=l,R=r;
		if(cnt[a[l]]==1)--now;
		--cnt[a[l]],++l;
	}
	cout<<L<<' '<<R<<'\n';
}