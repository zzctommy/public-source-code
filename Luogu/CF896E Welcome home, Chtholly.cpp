#include<bits/stdc++.h>
using namespace std;
#define rint register int
typedef long long LL;
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
inline int min(const int &a,const int &b) {return a<b?a:b;}
inline int max(const int &a,const int &b) {return a>b?a:b;}
const int N=100010;
const int M=330;
const int D=100000;
int n,m,a[N],b[N],l[M],r[M],len,mx[M],tag[M],blo[M][N],fa[N],bel[N],sum[N];
int find(int x) {return x==fa[x]?x:fa[x]=find(fa[x]);}
void build(int p) {
	for(rint i=l[p];i<=r[p];++i)
		a[i]=b[find(i)],blo[p][a[i]]=0,fa[i]=i,sum[i]=1;
	for(rint i=l[p];i<=r[p];++i) {
		if(!blo[p][a[i]])blo[p][a[i]]=i,b[i]=a[i];
		else sum[blo[p][a[i]]]+=sum[i],fa[i]=blo[p][a[i]];
	}
	while(!blo[p][mx[p]])--mx[p];
}
void change(int p,int x,int y,int v) {
	for(rint i=l[p];i<=r[p];++i)
		a[i]=b[find(i)],blo[p][a[i]]=0;
	for(rint i=x;i<=y;++i)
		if(b[find(i)]-tag[p]>v)a[i]-=v;
	for(rint i=l[p];i<=r[p];++i)
		b[i]=a[i],fa[i]=i;
	build(p);
}
void update(int L,int R,int V) {
	if(bel[L]==bel[R]) {change(bel[L],L,R,V);return;}
	change(bel[L],L,r[bel[L]],V);
	change(bel[R],l[bel[R]],R,V);
	for(rint i=bel[L]+1;i<bel[R];++i) {
		if(V>=mx[i]-tag[i])continue;
		if(mx[i]-tag[i]<=V*2) {
			for(rint j=tag[i]+1+V;j<=mx[i];++j) {
				if(blo[i][j]) {
					if(!blo[i][j-V])blo[i][j-V]=blo[i][j],b[blo[i][j]]=j-V,blo[i][j]=0;
					else fa[blo[i][j]]=blo[i][j-V],sum[blo[i][j-V]]+=sum[blo[i][j]],blo[i][j]=0;
			 	}
			}
			while(!blo[i][mx[i]])--mx[i];
		} else {
			for(rint j=tag[i]+1;j<=tag[i]+V;++j) {
				if(blo[i][j]) {
					if(!blo[i][j+V])blo[i][j+V]=blo[i][j],b[blo[i][j]]=j+V,blo[i][j]=0;
					else fa[blo[i][j]]=blo[i][j+V],sum[blo[i][j+V]]+=sum[blo[i][j]],blo[i][j]=0;
				}
			}
			tag[i]+=V;
		}
	}
}
int query(int L,int R,int V) {
	int res=0;
	if(bel[L]==bel[R]) {
		for(rint i=L;i<=R;++i)
			res+=(b[find(i)]-tag[bel[i]]==V);
		return res;
	}
	for(rint i=L;i<=r[bel[L]];++i)
		res+=(b[find(i)]-tag[bel[L]]==V);
	for(rint i=l[bel[R]];i<=R;++i)
		res+=(b[find(i)]-tag[bel[R]]==V);
	for(rint i=bel[L]+1;i<bel[R];++i)
		if(tag[i]+V<=D)res+=sum[blo[i][tag[i]+V]];
	return res;
}
signed main() {
	n=rd(),m=rd();len=sqrt(n);
	for(rint i=1;i<=n;++i)a[i]=rd();
	for(rint i=1;i<=n;++i)
		bel[i]=(i-1)/len+1,b[i]=a[i],fa[i]=i;
	for(rint i=1;i<=bel[n];++i)
		l[i]=(i-1)*len+1,r[i]=min(n,i*len);
	for(rint i=1;i<=bel[n];++i)mx[i]=D,build(i);
	while(m--) {
		int opt=rd(),L=rd(),R=rd(),X=rd();
		if(opt==1)update(L,R,X);
		else printf("%d\n",query(L,R,X));
	}
	return 0;
}