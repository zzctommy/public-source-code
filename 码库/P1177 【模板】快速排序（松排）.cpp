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
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return x;
}
const int N=100005;
int n;
unsigned a[N];
void Sort(unsigned int*a,int n){
	static unsigned int _b[N];
	static unsigned int*b=_b;
	static int cnt[256];
	for(int i=0;i<32;i+=8){
		memset(cnt,0,sizeof(cnt));
		for(int j=n-1;j>=0;--j)++cnt[(a[j]>>i)&255];
		for(int j=1;j<256;++j)cnt[j]+=cnt[j-1];
		for(int j=n-1;j>=0;--j)b[--cnt[(a[j]>>i)&255]]=a[j];
		swap(a,b);
	}
}
signed main(){
	n=read();
	for(int i=0;i<n;++i)a[i]=read();
	sort(a,a+n);
	for(int i=0;i<n;++i)printf("%d ",a[i]);
	return 0;
}