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

const int N=100005;
const int S1=720;
const int S2=200;
const int V=100000;
int n,m,a[N],L1[N/S1+5],R1[N/S1+5],L2[N/S2+5],R2[N/S2+5],n1,n2,bl1[N],bl2[N];
int F[N/S1+5][N],rev[N/S1+5][N];
int t1[N],t2[N/S2+5],t[N],tot;
int s1[N/S1+5][N],s2[N/S1+5][N/S2+5];
void init(){
	n1=(n-1)/S1+1,n2=(V-1)/S2+1;
	rep(i,1,n1)L1[i]=R1[i-1]+1,R1[i]=i*S1;
	rep(i,1,n2)L2[i]=R2[i-1]+1,R2[i]=i*S2;
	R1[n1]=n,R2[n2]=V;
	rep(i,1,n1)rep(j,L1[i],R1[i])bl1[j]=i;
	rep(i,1,n2)rep(j,L2[i],R2[i])bl2[j]=i;
	rep(bl,1,n1){
		rep(i,1,V)s1[bl][i]=s1[bl-1][i];
		rep(i,1,n2)s2[bl][i]=s2[bl-1][i];
		rep(i,L1[bl],R1[bl])++s1[bl][a[i]],++s2[bl][bl2[a[i]]],F[bl][a[i]]=a[i],rev[bl][a[i]]=a[i];
	}
}
void update(int l,int r,int x,int y){
	if(x==y)return;
	if(bl1[l]==bl1[r]){
		int bl=bl1[l],sum=0;
		if(s1[bl][x]-s1[bl-1][x]>0){
			rep(i,l,r)if(F[bl][a[i]]==x)++sum;
			if(!sum)return;
			rep(i,L1[bl],R1[bl])a[i]=F[bl][a[i]];
			rep(i,l,r)if(a[i]==x)a[i]=y;
			rep(i,L1[bl],R1[bl])F[bl][a[i]]=a[i],rev[bl][a[i]]=a[i];
			rep(i,bl,n1)s1[i][x]-=sum,s1[i][y]+=sum,s2[i][bl2[x]]-=sum,s2[i][bl2[y]]+=sum;
		}
		return;
	}
	int bl=bl1[l],br=bl1[r],sum=0,tmp;
	if(s1[bl][x]-s1[bl-1][x]>0){
		rep(i,L1[bl],R1[bl])a[i]=F[bl][a[i]];
		rep(i,l,R1[bl])if(a[i]==x)a[i]=y,++sum;
		rep(i,L1[bl],R1[bl])F[bl][a[i]]=a[i],rev[bl][a[i]]=a[i];
	}
	s1[bl][x]-=sum,s1[bl][y]+=sum,s2[bl][bl2[x]]-=sum,s2[bl][bl2[y]]+=sum;
	rep(i,bl+1,br-1){
		if(tmp=s1[i][x]-s1[i-1][x]-sum){
			if(s1[i][y]-s1[i-1][y]+sum==0)F[i][rev[i][x]]=y,rev[i][y]=rev[i][x];
			else {
				rep(j,L1[i],R1[i])a[j]=F[i][a[j]];
				rep(j,L1[i],R1[i])if(a[j]==x)a[j]=y;
				rep(j,L1[i],R1[i])F[i][a[j]]=a[j],rev[i][a[j]]=a[j];
			}
			sum+=tmp;
		}
		s1[i][x]-=sum,s1[i][y]+=sum,s2[i][bl2[x]]-=sum,s2[i][bl2[y]]+=sum;
	}
	if(s1[br][x]-s1[br-1][x]-sum>0){
		rep(i,L1[br],R1[br])a[i]=F[br][a[i]];
		rep(i,L1[br],r)if(a[i]==x)a[i]=y,++sum;
		rep(i,L1[br],R1[br])F[br][a[i]]=a[i],rev[br][a[i]]=a[i];
	}
	rep(i,br,n1)s1[i][x]-=sum,s1[i][y]+=sum,s2[i][bl2[x]]-=sum,s2[i][bl2[y]]+=sum;
}
int query(int l,int r,int k){
	if(bl1[l]==bl1[r]){
		int bl=bl1[l],it=1;
		rep(i,l,r){
			int x=F[bl][a[i]];
			++t1[x],++t2[bl2[x]],t[++tot]=x;
		}
		while(k>t2[it])k-=t2[it++];
		it=L2[it];
		while(k>t1[it])k-=t1[it++];
		rep(i,1,tot)t1[t[i]]=t2[bl2[t[i]]]=0;tot=0;
		return it;
	}
	int bl=bl1[l],br=bl1[r],it=1,tmp;
	rep(i,l,R1[bl]){
		int x=F[bl][a[i]];
		++t1[x],++t2[bl2[x]],t[++tot]=x;
	}
	rep(i,L1[br],r){
		int x=F[br][a[i]];
		++t1[x],++t2[bl2[x]],t[++tot]=x;
	}
	while(k>(tmp=s2[br-1][it]-s2[bl][it]+t2[it]))k-=tmp,++it;
	it=L2[it];
	while(k>(tmp=s1[br-1][it]-s1[bl][it]+t1[it]))k-=tmp,++it;
	rep(i,1,tot)t1[t[i]]=t2[bl2[t[i]]]=0;tot=0;
	return it;
}
signed main(){
	n=read(),m=read();
	rep(i,1,n)a[i]=read();
	init();
	while(m--){
		int op=read(),x=read(),y=read(),z=read();
		if(op==1)update(x,y,z,read());
		else printf("%d\n",query(x,y,z));
	}
	return 0;
}