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
#define FAIL return puts("No"),0
#define pc putchar
const int N=200005;
int a,b,k,S[N],T[N],n;
signed main(){
	a=read(),b=read(),k=read(),n=a+b;
	if(k==0){
		puts("Yes");
		rep(i,1,b)pc('1');rep(i,1,a)pc('0');puts("");
		rep(i,1,b)pc('1');rep(i,1,a)pc('0');puts("");
		return 0;
	}
	if(k>=a+b)FAIL;
	if(a==0){
		if(k)FAIL;
		else{
			puts("Yes");
			rep(i,1,b)pc('1');puts("");
			rep(i,1,b)pc('1');puts("");
		}
		return 0;
	}
	if(b==1){
		if(k)FAIL;
		else{
			puts("Yes");
			pc('1');rep(i,1,a)pc('0');puts("");
			pc('1');rep(i,1,a)pc('0');puts("");
		}
		return 0;
	}
	if(k==a+b-1)FAIL;
	S[1]=T[1]=1;
	S[2]=1,S[2+k]=0;
	T[2]=0,T[2+k]=1;
	b-=2,--a;
	rep(i,3,1+k)if(a)S[i]=T[i]=0,--a;else S[i]=T[i]=1,--b;
	rep(i,k+3,n)if(a)S[i]=T[i]=0,--a;else S[i]=T[i]=1,--b;
	puts("Yes");
	rep(i,1,n)pc(S[i]+'0');puts("");
	rep(i,1,n)pc(T[i]+'0');puts("");
}