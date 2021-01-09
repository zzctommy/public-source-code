#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=300005;
const int T=N*20;
int n,m,a[N];
int tot,val[T],ls[T],rs[T],root[N];
void update(int &p,int pre,int l,int r,int pos){
	p=++tot;
	ls[p]=ls[pre],rs[p]=rs[pre],val[p]=val[pre]+1;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(pos<=mid)update(ls[p],ls[pre],l,mid,pos);
	else update(rs[p],rs[pre],mid+1,r,pos);
}
int query(int p,int pre,int l,int r,int k){
	if(l==r)return l;
	int mid=(l+r)>>1,L=val[ls[p]]-val[ls[pre]],R=val[rs[p]]-val[rs[pre]],res;
	if(L>k){res=query(ls[p],ls[pre],l,mid,k);if(~res)return res;}
	if(R>k){res=query(rs[p],rs[pre],mid+1,r,k);if(~res)return res;}
	return -1;
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i)a[i]=read(),update(root[i],root[i-1],1,n,a[i]);
	while(m--){
		int l=read(),r=read(),k=read(),t=(r-l+1)/k;
		printf("%d\n",query(root[r],root[l-1],1,n,t));
	}
}
