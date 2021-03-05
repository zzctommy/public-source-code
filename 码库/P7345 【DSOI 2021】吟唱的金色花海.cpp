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
#define x0 fyyAKIOI
#define y0 FyyAKIOI
int t,x0,y0,k;
int ask(int x,int y){
	printf("0 %d %d\n",x,y),fflush(stdout);
	return read();
}
void print(int x,int y){
	printf("1 %d %d\n",x,y),fflush(stdout);
}
void Main(){
	t=read(),x0=read(),y0=read(),k=read();
	if(!t)return print(x0,y0);
	int a1=ask(x0,y0+1),a2=ask(x0-1,y0),a3,a4,l,r,o=t>>1,res;
	a3=!a1,a4=!a2; 
	if(a1&&a2){
		l=x0-t-o,r=x0-o;
		while(l<=r){
			int mid=(l+r)>>1;
			if(ask(mid,(mid-x0)+y0+t))res=mid,r=mid-1;
			else l=mid+1;
		}
		res+=o,print(res,(res-x0)+y0+t);
	}
	else if(a2&&a3){
		l=x0-t+o,r=x0+o;
		while(l<=r){
			int mid=(l+r)>>1;
			if(ask(mid,-(mid-x0)+y0-t))res=mid,l=mid+1;
			else r=mid-1;
		}
		res-=o,print(res,-(res-x0)+y0-t);
	}
	else if(a3&&a4){
		l=x0-o,r=x0+t-o;
		while(l<=r){
			int mid=(l+r)>>1;
			if(ask(mid,(mid-x0)+y0-t))res=mid,r=mid-1;
			else l=mid+1;
		}
		res+=o,print(res,(res-x0)+y0-t);
	}
	else if(a4&&a1){
		l=x0+o,r=x0+t+o;
		while(l<=r){
			int mid=(l+r)>>1;
			if(ask(mid,-(mid-x0)+y0+t))res=mid,l=mid+1;
			else r=mid-1;
		}
		res-=o,print(res,-(res-x0)+y0+t);
	}
}
signed main(){for(int T=read();T;--T)Main();}