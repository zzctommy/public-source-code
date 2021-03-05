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
const int N=25;
int n,a[N],sg[N],tag[N*N];
void Main(){
	int ans=0;
	n=read();per(i,n,1)a[i]=read();
	per(i,n,1)if(a[i]&1)ans^=sg[i];
	if(!ans)puts("-1 -1 -1\n0");
	else{
		int sum=0,x=-1,y=-1,z=-1;
		per(i,n,1)per(j,i-1,1)per(k,j,1)if((ans^sg[i]^sg[j]^sg[k])==0){
			++sum;
			if(!~x)x=n-i,y=n-j,z=n-k;
		}
		printf("%d %d %d\n%d\n",x,y,z,sum);
	}
}
void init(){
	sg[1]=0;
	rep(i,2,21){
		rep(j,1,i)rep(k,j,i-1)tag[sg[j]^sg[k]]=i;
		rep(j,0,624)if(tag[j]!=i){sg[i]=j;break;}
	}
}
signed main(){init();for(int T=read();T;--T)Main();}
/*
2
4
1 0 1 5000
3
0 0 1

*/