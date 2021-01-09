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
const int N=(1<<16)+5;
int n,a[N],lst[N];
const char QUE[3][5]={"XOR","OR","AND"};
int ask(int op,int x,int y){
	printf("%s %d %d\n",QUE[op],x,y),fflush(stdout);
	return read();
}
signed main(){
	scanf("%d",&n);
	rep(i,2,n)a[i]=ask(0,1,i);
	rep(i,1,n){
		if(lst[a[i]]){
			int x=ask(1,lst[a[i]],i);
			a[1]=x^a[i];
			printf("! %d",a[1]);
			rep(i,2,n)printf(" %d",a[1]^a[i]);puts("");fflush(stdout);
			return 0;
		}
		lst[a[i]]=i;
	}
	rep(i,1,n){
		if(a[i]==1)a[1]|=ask(2,1,i);
		if(a[i]==n-2)a[1]|=ask(1,1,i)&1;
	}
	printf("! %d",a[1]);
	rep(i,2,n)printf(" %d",a[1]^a[i]);puts("");fflush(stdout);
	return 0;

}
