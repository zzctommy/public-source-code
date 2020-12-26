#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=500005;
int n,m,a[N],ans[N],bel[N],S,num,L[N],R[N],lsh[N],len,nxt[N],pre[N],id[N],now;
struct QUE{int l,r,id;}q[N];
inline bool cmp(const QUE&a,const QUE&b){
	return bel[a.l]==bel[b.l]?a.r<b.r:a.l<b.l;
}
void brute(int k){
	int res=N;
	rep(i,q[k].l,q[k].r)if(pre[i]>=q[k].l)ckmin(res,i-pre[i]);
	ans[q[k].id]=res==N?-1:res;
}
void addr(int i,int l){if(pre[i]>=l)ckmin(now,i-pre[i]);}
void addl(int i,int r){if(nxt[i]<=r)ckmin(now,nxt[i]-i);}
signed main(){
	n=read(),m=read(),S=sqrt(n-1)+1,num=(n-1)/S+1;
	rep(i,1,n)a[i]=lsh[i]=read();
	sort(lsh+1,lsh+n+1),len=unique(lsh+1,lsh+n+1)-lsh-1;
	rep(i,1,n)a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
	fill(id+1,id+len+1,0);rep(i,1,n)pre[i]=id[a[i]],id[a[i]]=i;
	fill(id+1,id+len+1,n+1);per(i,n,1)nxt[i]=id[a[i]],id[a[i]]=i;
	rep(i,1,num)L[i]=R[i-1]+1,R[i]=i*S;R[num]=n;
	rep(i,1,num)rep(j,L[i],R[i])bel[j]=i;
	rep(i,1,m)q[i].id=i,q[i].l=read(),q[i].r=read();
	sort(q+1,q+m+1,cmp);
	for(int i=1,l=1,r=0,lst=0;i<=m;++i){
		if(bel[q[i].l]==bel[q[i].r]){brute(i);continue;}
		if(lst!=bel[q[i].l])lst=bel[q[i].l],now=N,l=R[bel[q[i].l]]+1,r=l-1;
		while(r<q[i].r)addr(++r,l);
		int l_=l,tmp=now;
		while(l_>q[i].l)addl(--l_,r);
		ans[q[i].id]=now==N?-1:now,now=tmp;
	}
	rep(i,1,m)printf("%d\n",ans[i]);
	return 0;
}