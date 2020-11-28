#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
inline unsigned long long readull(){
	unsigned long long x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return x;
}
#define N 1000005
#define mod 998244353
int n,m,c,k,p[N],q[N],cnt;
unsigned long long a[N],msk;
unsigned long long ans=1;
bool buy[70],ask[70];
signed main(){
	n=read(),m=read(),c=read(),k=read();
	if(n==0&&m==0&&k==64)return cout<<"18446744073709551616",0;
	for(int i=1;i<=n;++i)msk|=a[i]=readull();
	for(int i=1;i<=m;++i){
		p[i]=read(),q[i]=read();
		if(msk>>p[i]&1)buy[p[i]]=1;
		ask[p[i]]=1;
	}
	for(int i=0;i<k;++i)
		if(buy[i])++cnt;
		else if(!ask[i])++cnt;
	cerr<<cnt<<'\n';
	for(int i=1;i<=cnt;++i)ans<<=1;
	cout<<ans-n<<'\n';
	return 0;
}