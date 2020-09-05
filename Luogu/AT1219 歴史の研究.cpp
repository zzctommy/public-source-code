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
const int N=200010;
const int inf=2000000010;
int a[N],n,m;
int b[N],lsh[N],len,bin[N],bel[N],L[N],R[N],size,num,Bin[N];
LL sum,ans[N];
struct QUE {
	int l,r,id;
}que[N];
inline bool cmp(const QUE &a,const QUE &b) {
	return bel[a.l]!=bel[b.l]?bel[a.l]<bel[b.l]:a.r<b.r;
}
void brute(int l,int r,int x) {
	LL res=0;
	for(rint i=l;i<=r;++i)++Bin[b[i]];
	for(rint i=l;i<=r;++i)res=max(res,1ll*Bin[b[i]]*a[i]);
	for(rint i=l;i<=r;++i)--Bin[b[i]];
	ans[x]=res;
}
void pop(int x) {--bin[b[x]];}
void add(int x,LL &sum) {sum=max(sum,1ll*(++bin[b[x]])*a[x]);}
signed main() {
	n=rd(),m=rd(),size=sqrt(n),num=(n-1)/size+1;
	for(rint i=1;i<=n;++i)lsh[++len]=a[i]=rd();
	for(rint i=1;i<=m;++i)que[i].l=rd(),que[i].r=rd(),que[i].id=i;
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(rint i=1;i<=n;++i)b[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
	for(rint i=1;i<=n;++i)bel[i]=(i-1)/size+1;
	for(rint i=1;i<=num;++i)L[i]=(i-1)*size+1,R[i]=i*size;R[num]=n;
	sort(que+1,que+m+1,cmp);
	for(rint i=1,l=1,r=0,lst=0;i<=m;++i) {
		if(bel[que[i].l]==bel[que[i].r]) {brute(que[i].l,que[i].r,que[i].id);continue;}
		if(lst!=bel[que[i].l]) {
			while(r>R[bel[que[i].l]])pop(r--);
			while(l<R[bel[que[i].l]]+1)pop(l++);
			sum=0,lst=bel[que[i].l];
		}
		while(r<que[i].r)add(++r,sum);
		int l_=l;LL tmp=sum;
		while(l_>que[i].l)add(--l_,tmp);
		ans[que[i].id]=tmp;
		while(l_<l)pop(l_++);
	}
	for(rint i=1;i<=m;++i)printf("%lld\n",ans[i]);
	return 0;
}