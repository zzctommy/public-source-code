#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=1600010;
struct num {
	int a[N],len;
	num(){memset(a,0,sizeof(a)),len=0;}
	void read() {
		char ch=getchar();
		while(!isdigit(ch))ch=getchar();
		while(isdigit(ch))a[len++]=ch-'0',ch=getchar();
		reverse(a,a+len);
	}
	void init(LL x) {
		while(x)a[len++]=x%10,x/=10;
	}
	void print(char c=-1) {
		printf("%d",a[len-1]);
		for(rint i=len-2;i>=0;--i)putchar(a[i]+'0');
		if(~c)putchar(c);
	}
};
struct cp {
	double x,y;
	cp(){x=y=0;}
	cp(double x_,double y_){x=x_,y=y_;}
	cp operator + (const cp &t) {return cp(x+t.x,y+t.y);}
	cp operator - (const cp &t) {return cp(x-t.x,y-t.y);}
	cp operator * (const cp &t) {return cp(x*t.x-y*t.y,x*t.y+y*t.x);}
}A[N],B[N];
const double pi=acos(-1.0);
int rev[N],lg,lim;
num operator / (const num &a,const int &b) {
	num c;int mx=a.len;
	LL now=0;
	for(rint i=mx-1,s=0;~i;--i) {
		now=now*10+a.a[i];
		if(now/b)s=1;
		if(!s)continue;
		c.a[c.len++]=now/b;
		now%=b;
	}
	reverse(c.a,c.a+c.len);
	return c;
}
void init(int n) {
	for(lim=1,lg=0;lim<=n;lim<<=1,++lg);
	for(rint i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
}
void FFT(cp *a,int o) {
	for(rint i=0;i<lim;++i)
		if(rev[i]<i)swap(a[rev[i]],a[i]);
	for(rint i=1;i<lim;i<<=1) {
		cp wn=cp(cos(pi/i),o*sin(pi/i));
		for(rint j=0;j<lim;j+=(i<<1)) {
			cp w0=cp(1,0);
			for(rint k=0;k<i;++k,w0=w0*wn) {
				cp X=a[j+k],Y=w0*a[i+j+k];
				a[j+k]=X+Y;
				a[i+j+k]=X-Y;
			}
		}
	}
}
num fastmul(const num &a,const num &b) {
	num c;int len=a.len+b.len;init(len),c.len=lim;
	for(rint i=0,mx=a.len;i<mx;++i)A[i]=cp(a.a[i],0);for(rint i=a.len;i<lim;++i)A[i]=cp(0,0);
	for(rint i=0,mx=b.len;i<mx;++i)B[i]=cp(b.a[i],0);for(rint i=b.len;i<lim;++i)B[i]=cp(0,0);
	FFT(A,1),FFT(B,1);
	for(rint i=0;i<lim;++i)A[i]=A[i]*B[i];
	FFT(A,-1);
	for(rint i=0;i<lim;++i)c.a[i]=(int)(A[i].x/lim+0.5);
	for(rint i=0;i<lim;++i)if(c.a[i]>=10)c.a[i+1]+=c.a[i]/10,c.a[i]%=10;
	while(c.len&&!c.a[c.len-1])--c.len;
	return c;
}
num operator + (const num &a,const int &x) {
	num b;b.init(x);
	num c;int mx=max(a.len,b.len);c.len=mx;
	for(rint i=0;i<mx;++i)c.a[i]=a.a[i]+b.a[i];
	for(rint i=0;i<mx;++i)if(c.a[i]>9)++c.a[i+1],c.a[i]-=10;
	if(c.a[c.len])++c.len;
	return c;
}
num a,ans;
signed main() {
	a.read();
	ans=fastmul(a+1,a+2);
	ans=fastmul(ans,a+3);
	ans=fastmul(ans,a+4);
	ans=ans/24;
	ans.print();
}
