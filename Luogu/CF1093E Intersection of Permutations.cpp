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
const int N=200010;
const int M=32400000;
int n,m,a[N],b[N],c[N];
int val[M],ch[M][2],tot,rub[M],top,root[N];
#define lt(i) (i&(-i))
int ne() {return top?rub[top--]:++tot;}
void ins(int &x,int l,int r,int pos,int w) {
	if(!x)x=ne();
	val[x]+=w;
	if(l==r) {if(!val[x])rub[++top]=x,x=0;return;}
	int mid=(l+r)>>1;
	if(mid>=pos)ins(ch[x][0],l,mid,pos,w);
	else ins(ch[x][1],mid+1,r,pos,w);
	if(!val[x])rub[++top]=x,x=0;
}
int query(int x,int ql,int qr,int l,int r) {
	if(!x)return 0;
	if(ql<=l&&r<=qr)return val[x];
	int mid=(l+r)>>1,res=0;
	if(mid>=ql)res+=query(ch[x][0],ql,qr,l,mid);
	if(mid<qr)res+=query(ch[x][1],ql,qr,mid+1,r);
	return res;
}
void add(int t,int x,int w) {
	for(rint i=t;i<=n;i+=lt(i))ins(root[i],1,n,x,w);
}
int ask(int ql,int qr,int l,int r) {
	int res=0;
	for(rint i=ql-1;i>0;i-=lt(i))res-=query(root[i],l,r,1,n);
	for(rint i=qr;i>0;i-=lt(i))res+=query(root[i],l,r,1,n);
	return res;
}
signed main() {
	n=rd(),m=rd();
	for(rint i=1;i<=n;++i)a[rd()]=i;
	for(rint i=1;i<=n;++i)b[i]=a[rd()];
	for(rint i=1;i<=n;++i)add(i,b[i],1);
	while(m--) {
		int opt=rd();
		if(opt==1) {
			int l1=rd(),r1=rd(),l2=rd(),r2=rd();
			printf("%d\n",ask(l2,r2,l1,r1));
		} else {
			int x=rd(),y=rd();
			add(x,b[x],-1),add(y,b[y],-1);
			swap(b[x],b[y]);
			add(x,b[x],1),add(y,b[y],1);
		}
	}
	return 0;
}