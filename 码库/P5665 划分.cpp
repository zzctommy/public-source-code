#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#include<bits/stdc++.h>
using namespace std;
#define rint register int
typedef long long LL;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
const int N=4e7+10;
const int M=1e5+10;
const int mod=(1<<30)-1;
int a[N],n,q[N],H,T,typ,pre[N];
int p[M],l[M],r[M],b[N];
LL sum[N];
const int base=1000000000;
const int limit=9;
int power_10[13]={1,10,100,1000,1000,10000,100000,1000000,10000000,100000000,1000000000};
struct num {
	LL a[12];
	num(){memset(a,0,sizeof(a));}
	void init(LL x) {
		a[0]=0;
		while(x)a[++a[0]]=x%base,x/=base;
	}
	void print(char c=-1) {
		printf("%lld",a[a[0]]);
		for(rint i=a[0]-1;i>0;--i)printf("%0*lld",limit,a[i]);
		if(~c)putchar(c);
	}
}ans;
num operator + (const num &a,const num &b) {
	num c;int mx=max(a.a[0],b.a[0]);c.a[0]=mx;
	for(rint i=1;i<=mx;++i)c.a[i]=a.a[i]+b.a[i];
	for(rint i=1;i<=mx;++i)if(c.a[i]>=base)++c.a[i+1],c.a[i]-=base;
	if(c.a[c.a[0]+1])++c.a[0];
	return c;
}
num operator * (const num &a,const num &b) {
	num c;int mx=a.a[0]+b.a[0]-1;c.a[0]=mx;
	for(rint i=1,mxa=a.a[0];i<=mxa;++i)
		for(rint j=1,mxb=b.a[0];j<=mxb;++j) {
			c.a[i+j-1]+=a.a[i]*b.a[j];
			if(c.a[i+j-1]>=base)c.a[i+j]+=c.a[i+j-1]/base,c.a[i+j-1]%=base;
		}
	if(c.a[c.a[0]+1])++c.a[0];
	return c; 
}
#define val(i) ((sum[i]<<1)-sum[pre[i]])
signed main() {
//	freopen("ac.in","r",stdin);
	n=rd(),typ=rd();
	if(!typ)for(rint i=1;i<=n;++i)a[i]=rd();
	else {
		int x=rd(),y=rd(),z=rd();b[1]=rd(),b[2]=rd();int m=rd();
		for(rint i=1;i<=m;++i)p[i]=rd(),l[i]=rd(),r[i]=rd();
		for(rint i=3;i<=n;++i)b[i]=((((1ll*x*b[i-1]&mod)+(1ll*y*b[i-2]&mod))&mod)+(z&mod))&mod;
		for(rint i=1;i<=m;++i) {
			for(rint j=p[i-1]+1;j<=p[i];++j)
				a[j]=b[j]%(r[i]-l[i]+1)+l[i];
		}
	}
	for(rint i=1;i<=n;++i)sum[i]=sum[i-1]+a[i];
	for(rint i=1;i<=n;++i) {
		while(H<T&&val(q[H+1])<=sum[i])++H;
		pre[i]=q[H];
		while(H<=T&&val(i)<=val(q[T]))--T;
		q[++T]=i;
	}
	num tmp;
	for(rint i=n;i;i=pre[i]) {
		tmp.init(sum[i]-sum[pre[i]]);
		ans=ans+(tmp*tmp);
	}
	ans.print('\n');
	return 0;
}
