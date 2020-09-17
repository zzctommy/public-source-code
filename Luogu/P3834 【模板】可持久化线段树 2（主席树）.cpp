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
const int N=200005;
const int T=N*20;
int n,m,a[N],cpy[N],len;
int root[N],tot,val[T],ls[T],rs[T];
void update(int &p,int pre,int l,int r,int v){
	p=++tot;
	ls[p]=ls[pre],rs[p]=rs[pre],val[p]=val[pre]+1;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(v<=mid)update(ls[p],ls[pre],l,mid,v);
	else update(rs[p],rs[pre],mid+1,r,v);
}
int query(int p,int pre,int l,int r,int k){
	if(l==r)return l;
	int mid=(l+r)>>1,x=val[ls[p]]-val[ls[pre]];
	if(k<=x)return query(ls[p],ls[pre],l,mid,k);
	else return query(rs[p],rs[pre],mid+1,r,k-x);
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i)a[i]=cpy[++len]=read();
	sort(cpy+1,cpy+len+1),len=unique(cpy+1,cpy+len+1)-cpy-1;
	for(int i=1;i<=n;++i)a[i]=lower_bound(cpy+1,cpy+len+1,a[i])-cpy;
	for(int i=1;i<=n;++i)update(root[i],root[i-1],1,len,a[i]);
	while(m--){
		int x=read(),y=read(),z=read();
		printf("%d\n",cpy[query(root[y],root[x-1],1,len,z)]);
	}
	return 0;
}
