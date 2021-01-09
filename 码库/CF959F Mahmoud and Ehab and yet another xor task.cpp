#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int mod=1000000007;
const int N=100010;
int n,m,d[30],a[N],ans[N],sum,lst;
struct node{
	int l,x,id;
}q[N];
bool cmp(const node &a,const node &b) {
	return a.l<b.l; 
}
void add(int x) {
	for(rint i=20;i>=0;--i) {
		if(x&(1<<i)) {
			if(d[i])x^=d[i];
			else {
				d[i]=x,++sum;break;
			}
		}
	}
}
int qpow(int n,int k,int mod) {
	int res=1;
	while(k) {
		if(k&1)res=1ll*res*n%mod;
		n=1ll*n*n%mod,k>>=1;
	}
	return res;
}
int query(int x) {
	for(rint i=20;i>=0;--i)
		if(x&(1<<i)) {
			if(d[i])x^=d[i];
			else return 0;
		}
	return qpow(2,lst-sum,mod);
}
signed main() {
	n=rd(),m=rd();
	for(rint i=1;i<=n;++i)a[i]=rd();
	for(rint i=1;i<=m;++i)q[i].l=rd(),q[i].x=rd(),q[i].id=i;
	sort(q+1,q+m+1,cmp);
	for(rint i=1;i<=m;++i) {
		while(lst<q[i].l)add(a[++lst]);
		ans[q[i].id]=query(q[i].x);
	}
	for(rint i=1;i<=m;++i)printf("%d\n",ans[i]);
	return 0;
}