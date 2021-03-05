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
const int N=110005;
int n,m,a[N],ans[N],top;
unsigned long long val[70],q[N],stk[N];
signed main(){
	scanf("%d",&n);
	rep(i,1,n){
		char str[6];
		scanf("%s",str+1);
		if(str[1]=='!')a[i]=-1;
		else if(str[1]=='&')a[i]=-2;
		else if(str[1]=='|')a[i]=-3;
		else if(str[1]=='^')a[i]=-4;
		else rep(j,1,strlen(str+1))a[i]=a[i]*10+str[j]-'0';
	}
	scanf("%d",&m);
	rep(i,1,m)scanf("%llu",&q[i]);
	for(int i=1;i<=m;i+=64){
		for(int j=0;j<64;++j)val[j]=0;
		for(int j=0;j<64;++j)
			for(int k=0;k<64;++k)
				val[k]|=(1ull<<j)*(q[i+j]>>k&1);
		top=0;
		for(int j=1;j<=n;++j){
			if(a[j]<0){
				if(a[j]==-1)stk[top]^=-1ull;
				else{
					unsigned long long X=stk[top--];
					if(a[j]==-2)stk[top]&=X;
					else if(a[j]==-3)stk[top]|=X;
					else stk[top]^=X;
				}
			}else stk[++top]=val[a[j]];
		}
		for(int j=0;j<64;++j)ans[i+j]=stk[1]>>j&1;
	}
	rep(i,1,m)putchar(ans[i]+'0');
	return 0;
}