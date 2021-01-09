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
const int N=100010;
int n,q,a[N],lsh[N<<1],len,cnt[N<<1],nowc,nq,nc,opt[N],sz,bel[N],bin[N<<1],ans[N];
struct QUE {
	int id,l,r,pre;
}que[N];
struct UPD {
	int x,y;
}upd[N];
bool cmp(const QUE &a,const QUE &b) {
	if(bel[a.l]!=bel[b.l])return bel[a.l]<bel[b.l];
	if(bel[a.r]!=bel[b.r])return bel[a.r]<bel[b.r];
	return a.pre<b.pre;
}
void pop(int x) {--bin[cnt[x]],--cnt[x],++bin[cnt[x]];}
void add(int x) {--bin[cnt[x]],++cnt[x],++bin[cnt[x]];}
void modify(int x,int i) {
	if(que[i].l<=upd[x].x&&upd[x].x<=que[i].r) {
		pop(a[upd[x].x]);
		add(upd[x].y);
	}
	swap(a[upd[x].x],upd[x].y);
}
int mex() {
	for(rint i=1;i<=n;++i)if(!bin[i])return i;
}
signed main() {
	n=rd(),q=rd(),sz=ceil(pow(n,0.666));
	for(rint i=1;i<=n;++i)a[i]=lsh[++len]=rd(),bel[i]=(i-1)/sz+1;
	for(rint i=1;i<=q;++i) {
		opt[i]=rd();
		if(opt[i]&1) {
			++nq;
			que[nq].id=nq;
			que[nq].l=rd();
			que[nq].r=rd();
			que[nq].pre=nc;
		} else {
			++nc;
			upd[nc].x=rd();
			lsh[++len]=upd[nc].y=rd();
		}
	}
	sort(lsh+1,lsh+len+1);len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(rint i=1;i<=n;++i)a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
	for(rint i=1;i<=nc;++i)upd[i].y=lower_bound(lsh+1,lsh+len+1,upd[i].y)-lsh;
	sort(que+1,que+nq+1,cmp);
	for(rint i=1,l=1,r=0;i<=nq;++i) {
		while(l<que[i].l)pop(a[l++]);
		while(l>que[i].l)add(a[--l]);
		while(r<que[i].r)add(a[++r]);
		while(r>que[i].r)pop(a[r--]);
		while(nowc<que[i].pre)modify(++nowc,i);
		while(nowc>que[i].pre)modify(nowc--,i);
		ans[que[i].id]=mex();
	}
	for(rint i=1;i<=nq;++i)printf("%d\n",ans[i]);
	return 0;
}