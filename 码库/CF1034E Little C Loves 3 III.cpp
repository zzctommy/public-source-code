#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
int rdc(){
	char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	return ch-'0';
}
const int N=1<<21;
int n,m;
LL a[N],b[N];
void fwt(LL*a,int op){
	for(int i=1;i<m;i<<=1)
		for(int j=0;j<m;j+=i<<1)
			for(int k=0;k<i;++k)
				a[i+j+k]+=a[j+k]*op;
}
signed main(){
	m=(1<<(n=read()));
	for(int i=0;i<m;++i)a[i]=(1ll<<(__builtin_popcount(i)<<1))*rdc();
	for(int i=0;i<m;++i)b[i]=(1ll<<(__builtin_popcount(i)<<1))*rdc();
	fwt(a,1),fwt(b,1);
	for(int i=0;i<m;++i)a[i]*=b[i];
	fwt(a,-1);
	for(int i=0;i<m;++i)putchar('0'+((a[i]>>(__builtin_popcount(i)<<1))&3));
	puts("");
	return 0;
}