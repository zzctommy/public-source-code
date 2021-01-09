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
int rdopt(){
	char ch=getchar();
	while(ch!='A'&&ch!='M')ch=getchar();
	return ch=='A';
}
const int N=1000005;
const int S=1000;
int n,q,a[N],b[N],tag[N];
int num,L[N/S+5],R[N/S+5],bel[N];
void rebuild(int id){
	rep(i,L[id],R[id])b[i]=a[i]+tag[id];
	tag[id]=0,sort(b+L[id],b+R[id]+1);
}
void build(){
	num=(n-1)/S+1;
	rep(i,1,num)L[i]=R[i-1]+1,R[i]=i*S;R[num]=n;
	rep(i,1,num){
		rebuild(i);
		rep(j,L[i],R[i])bel[j]=i;
	}
}
void update(int l,int r,int x){
	if(bel[l]+1>=bel[r]){
		rep(i,l,r)a[i]+=x;
		rebuild(bel[l]),rebuild(bel[r]);
		return;
	}
	rep(i,l,R[bel[l]])a[i]+=x;
	rep(i,L[bel[r]],r)a[i]+=x;
	rebuild(bel[l]),rebuild(bel[r]);
	rep(i,bel[l]+1,bel[r]-1)tag[i]+=x;
}
int calc(int*a,int L,int R,int k){
	int l=L,r=R,res=L-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(a[mid]<=k)l=mid+1,res=mid;
		else r=mid-1;
	}
	return res-L+1;
}
int query(int l,int r,int x){
	int res=0;
	if(bel[l]+1>=bel[r]){
		rep(i,l,r)if(a[i]+tag[bel[i]]<=x)++res;
		return res;
	}
	rep(i,l,R[bel[l]])if(a[i]+tag[bel[l]]<=x)++res;
	rep(i,L[bel[r]],r)if(a[i]+tag[bel[r]]<=x)++res;
	rep(i,bel[l]+1,bel[r]-1)res+=calc(b,L[i],R[i],x-tag[i]);
	return res;
}
signed main(){
	n=read(),q=read();
	rep(i,1,n)a[i]=read();
	build();
	while(q--){
		int opt=rdopt(),l=read(),r=read(),x=read();
		if(opt)printf("%d\n",r-l+1-query(l,r,x-1));
		else update(l,r,x);
	}
	return 0;
}