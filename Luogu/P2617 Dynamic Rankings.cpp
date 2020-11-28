#include<bits/stdc++.h>
using namespace std;
#define rint register int
#define lowbit(i) (i&(-i))
typedef long long LL;
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
const int N=100010;
int ls[N*170],rs[N*170],val[N*170],rt[N];
int n,m,a[N],b[N<<1],num,tot;
int L[40],R[40],tl,tr;
struct QUERY {
	int opt,x,y,z;
}que[N];
void update(int &o,int l,int r,int pos,int w) {
	if(!o)o=++tot;val[o]+=w;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(pos<=mid)update(ls[o],l,mid,pos,w);
	else update(rs[o],mid+1,r,pos,w);
}
int query(int l,int r,int k) {
	if(l==r)return l;
	int suml=0,sumr=0;
	for(rint i=1;i<=tl;++i)suml+=val[ls[L[i]]];
	for(rint i=1;i<=tr;++i)sumr+=val[ls[R[i]]];
	int mid=(l+r)>>1;
	if(sumr-suml>=k) {
		for(rint i=1;i<=tl;++i)L[i]=ls[L[i]];
		for(rint i=1;i<=tr;++i)R[i]=ls[R[i]];
		return query(l,mid,k);
	} else {
		for(rint i=1;i<=tl;++i)L[i]=rs[L[i]];
		for(rint i=1;i<=tr;++i)R[i]=rs[R[i]];
		return query(mid+1,r,k-(sumr-suml));
	}
}
signed main() {
	n=rd(),m=rd();
	for(rint i=1;i<=n;++i)a[i]=b[++num]=rd();
	char opt[6];
	for(rint i=1;i<=m;++i) {
		scanf("%s",opt);
		que[i].opt=(opt[0]=='Q');
		if(que[i].opt)que[i].x=rd(),que[i].y=rd(),que[i].z=rd();
		else que[i].x=rd(),b[++num]=que[i].y=rd();
	}
	sort(b+1,b+num+1);
	num=unique(b+1,b+num+1)-b-1;
	for(rint i=1;i<=n;++i) {
		int tmp=lower_bound(b+1,b+num+1,a[i])-b;
		for(rint j=i;j<=n;j+=lowbit(j)) {
			update(rt[j],1,num,tmp,1);
		}
	}
	for(rint i=1;i<=m;++i) {
		if(que[i].opt) {
			tl=tr=0;--que[i].x;
			for(rint j=que[i].x;j>0;j-=lowbit(j))L[++tl]=rt[j];
			for(rint j=que[i].y;j>0;j-=lowbit(j))R[++tr]=rt[j];
			printf("%d\n",b[query(1,num,que[i].z)]);
		} else {
			int tmp=lower_bound(b+1,b+num+1,a[que[i].x])-b;
			for(rint j=que[i].x;j<=n;j+=lowbit(j))
				update(rt[j],1,num,tmp,-1);
			a[que[i].x]=que[i].y;
			tmp=lower_bound(b+1,b+num+1,que[i].y)-b;
			for(rint j=que[i].x;j<=n;j+=lowbit(j))
				update(rt[j],1,num,tmp,1);
		}
	}
	return 0;
} 