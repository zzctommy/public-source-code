#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define mkp(x,y) make_pair(x,y)
#define fi first
#define se second
#define pb(x) push_back(x)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
#define S 800
#define N 100005
int n,m,a[N],up,down;
typedef pair<int,int> pii;
pii b[N],t1[S],t2[S];
int num,L[N/5],R[N/S+5],bel[N];
int cnt1,cnt2,tag[N/S+5];
void init(){
	num=(n-1)/S+1;
	for(int i=1;i<=num;++i)L[i]=R[i-1]+1,R[i]=i*S;
	R[num]=n;
	for(int i=1;i<=num;++i){
		for(int j=L[i];j<=R[i];++j)
			bel[j]=i,b[j].fi=a[j],b[j].se=j;
		sort(b+L[i],b+R[i]+1);
	}
}
void rebuild(int id,int l,int r,int delta){
	cnt1=0,cnt2=0;
	for(int i=L[id];i<=R[id];++i)
		if(b[i].se>=l&&b[i].se<=r)t1[++cnt1]=mkp(b[i].fi+delta+tag[id],b[i].se);
		else t2[++cnt2]=mkp(b[i].fi+tag[id],b[i].se);
	tag[id]=0;
	int i=L[id],j=1,k=1;
	while(j<=cnt1&&k<=cnt2)b[i++]=t1[j]<t2[k]?t1[j++]:t2[k++];
	while(j<=cnt1)b[i++]=t1[j++];
	while(k<=cnt2)b[i++]=t2[k++];
}
void update(int l,int r,int k){
	k>0?up+=k:down+=k;
	int bl=bel[l],br=bel[r];
	if(bl==br){
		rebuild(bl,l,r,k);
		return;
	}
	for(int i=bl+1;i<br;++i)tag[i]+=k;
	rebuild(bl,l,R[bl],k),rebuild(br,L[br],r,k);
}
int calc(int l,int r,int k,pii*b){
	int ll=l,rr=r,ret=0;
	while(ll<=rr){
		int mid=(ll+rr)>>1;
		if(b[mid].fi<=k)ret=mid-l+1,ll=mid+1;
		else rr=mid-1;
	}
	return ret;
}
int ask(int l,int r,int k){
	int res=0;
	int bl=bel[l],br=bel[r];
	for(int i=bl+1;i<br;++i)res+=calc(L[i],R[i],k-tag[i],b);
	res+=calc(1,cnt1,k-tag[bl],t1);
	res+=calc(1,cnt2,k-tag[br],t2);
	return res;
}
int query(int l,int r,int k){
	if(k>r-l+1)return -1;
	int bl=bel[l],br=bel[r];
	if(bl==br){
		cnt1=0;
		for(int i=L[bl];i<=R[br];++i)if(b[i].se>=l&&b[i].se<=r)t1[++cnt1]=b[i];
		return t1[k].fi+tag[bl];
	}
	cnt1=0,cnt2=0;
	for(int i=L[bl];i<=R[bl];++i)if(b[i].se>=l&&b[i].se<=r)t1[++cnt1]=b[i];
	for(int i=L[br];i<=R[br];++i)if(b[i].se>=l&&b[i].se<=r)t2[++cnt2]=b[i];
	int ll=down,rr=up,res;
	while(ll<=rr){
		int mid=(ll+rr)>>1,t=ask(l,r,mid);
		if(t>=k)res=mid,rr=mid-1;
		else ll=mid+1;
	}
	return res;
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i)a[i]=read(),up=max(up,a[i]),down=min(down,a[i]);
	init();
	while(m--){
		int opt=read(),l=read(),r=read(),k=read();
		if(opt==1)printf("%d\n",query(l,r,k));
		else update(l,r,k);
	}
}
