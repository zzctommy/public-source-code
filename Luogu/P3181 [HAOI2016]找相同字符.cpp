#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=4e5+5;
int n,t[N],x[N],y[N],sa[N],rk[N],height[N];
int lena,lenb,st[N],top,lp[N],rp[N];
LL ans,f[N];
char s[N],A[N],B[N];
void get_SA() {
	memset(sa,0,sizeof(sa));
	memset(x,0,sizeof(x));
	memset(y,0,sizeof(y));
	int m='~',num;
	for(int i=1;i<=m;++i)t[i]=0;
	for(int i=1;i<=n;++i)++t[x[i]=s[i]];
	for(int i=1;i<=m;++i)t[i]+=t[i-1];
	for(int i=n;i>=1;--i)sa[t[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1) {
		num=0;
		for(int i=1;i<=m;++i)t[i]=0;
		for(int i=n-k+1;i<=n;++i)y[++num]=i;
		for(int i=1;i<=n;++i)if(sa[i]>k)y[++num]=sa[i]-k;
		for(int i=1;i<=n;++i)++t[x[i]];
		for(int i=2;i<=m;++i)t[i]+=t[i-1];
		for(int i=n; i>=1;--i)sa[t[x[y[i]]]--]=y[i];
		swap(x,y);x[sa[1]]=1,num=1;
		for(int i=2;i<=n;++i)
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?num:++num;
		if(num==n)break;m=num;
	}
}
void get_Height() {
	for(int i=1;i<=n;++i)rk[sa[i]]=i;
	for(int i=1,k=0;i<=n;++i) {
		if(rk[i]==1)continue;
		if(k)--k;
		int j=sa[rk[i]-1];
		while(j+k<=n&&i+k<=n&&s[j+k]==s[i+k])++k;
		height[rk[i]]=k;
	}
}
void solve(int flg) {
	get_SA(),get_Height();
	top=0;
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;++i) {
		while(top&&height[st[top]]>=height[i])--top;
		f[i]=f[st[top]]+height[i]*(i-st[top]);
		st[++top]=i;
	}
	for(int i=1;i<=n;++i)ans+=f[i]*flg;
}
signed main() {
	scanf("%s%s",A+1,B+1);
	lena=strlen(A+1),lenb=strlen(B+1),n=lena+lenb+1;
	for(int i=1;i<=lena;++i)s[i]=A[i];
	s[lena+1]='~';
	for(int i=1;i<=lenb;++i)s[i+lena+1]=B[i];
	solve(1);
	for(int i=1;i<=lena;++i)s[i]=A[i];n=lena;
	solve(-1);
	for(int i=1;i<=lenb;++i)s[i]=B[i];n=lenb;
	solve(-1);
	printf("%lld\n",ans);
	return 0;
}