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
inline void write(int w,char text=-1){
    if(!w)putchar(48);
    else{
        int d[10];
        for(d[0]=0;w;d[++d[0]]=w%10,w/=10);
        for(;d[0];putchar(d[d[0]--]^48));
    }
    if(~text)putchar(text);
}
const int N=150000;
const int M=1000010;
int a[N],n,m,bel[N],len,ans[N],nowsum,nowupd,numq,numu,cnt[M];
struct QUE {
	int id,l,r,pre;
}que[N];
struct UPD {
	int id,pos,k;
}upd[N];
bool cmp(const QUE &a,const QUE &b) {
	return bel[a.l]!=bel[b.l]?bel[a.l]<bel[b.l]:bel[a.r]!=bel[b.r]?bel[a.l]&1?bel[a.r]<bel[b.r]:bel[a.r]>bel[b.r]:a.pre<b.pre;
}
inline void pop(int x) {nowsum-=!--cnt[x];}
inline void add(int x) {nowsum+=!cnt[x]++;}
inline void swap(int &x,int &y) {x^=y^=x^=y;}
inline void modify(int x,int y) {
	if(que[y].l<=upd[x].pos&&upd[x].pos<=que[y].r) 
		pop(a[upd[x].pos]),add(upd[x].k);
	swap(upd[x].k,a[upd[x].pos]);
}
signed main() {
	n=rd(),m=rd(),len=ceil(pow(n,0.666));
	for(rint i=1;i<=n;++i)a[i]=rd(),bel[i]=(i-1)/len+1;
	for(rint i=1;i<=m;++i) {
		char ch=getchar();
		while(ch!='Q'&&ch!='R')ch=getchar();
		if(ch=='Q') {
			++numq;
			que[numq].id=numq;
			que[numq].l=rd();
			que[numq].r=rd();
			que[numq].pre=numu;
		} else {
			++numu;
			upd[numu].id=numu;
			upd[numu].pos=rd();
			upd[numu].k=rd();
		}
	}
	sort(que+1,que+numq+1,cmp);
	for(rint i=1,l=1,r=0;i<=numq;++i) {
		while(l<que[i].l)pop(a[l++]);
		while(l>que[i].l)add(a[--l]);
		while(r<que[i].r)add(a[++r]);
		while(r>que[i].r)pop(a[r--]);
		while(nowupd<que[i].pre)modify(++nowupd,i);
		while(nowupd>que[i].pre)modify(nowupd--,i);
		ans[que[i].id]=nowsum;
	}
	for(rint i=1;i<=numq;++i)write(ans[i],10);
	return 0;
} 
