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
const int N=20;
const int mod=1e9+9;
void fmod(int&x){x+=x>>31&mod,x-=mod,x+=x>>31&mod;}
int n,m,a[N+1][1<<N],b[N+1][1<<N],c[N+1][1<<N],cnt[1<<N];
void fwt(int*a,int n,int op){
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<n;j+=i<<1)
			for(int k=0;k<i;++k)
				fmod(a[i+j+k]+=a[j+k]*op);
}
signed main(){
	m=1<<(n=read());
	for(int i=0;i<m;++i)cnt[i]=cnt[i>>1]+(i&1);
	for(int i=0;i<m;++i)a[cnt[i]][i]=read();
	for(int i=0;i<m;++i)b[cnt[i]][i]=read();
	for(int i=0;i<=n;++i)fwt(a[i],m,1),fwt(b[i],m,1);
	for(int i=0;i<=n;++i)
		for(int j=0;j<=i;++j)
			for(int k=0;k<m;++k)
				fmod(c[i][k]+=1ll*a[j][k]*b[i-j][k]%mod);
	for(int i=0;i<=n;++i)fwt(c[i],m,-1);
	for(int i=0;i<m;++i)printf("%d ",c[cnt[i]][i]);
	return 0;
}