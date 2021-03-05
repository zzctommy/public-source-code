#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
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
int n,k,tot,a[2005][2005];
signed main(){
//	freopen("1.out","w",stdout);
	n=38*37+1,k=38;
	printf("%d %d\n",n,k);
	tot=1;
	rep(i,0,k-1){
		printf("%d ",a[i][0]=1);
		rep(j,1,k-1)printf("%d ",a[i][j]=++tot);
		puts("");
	}
	int c=0,d=1371;
	for(int i=0;i<k-1;++i){
		for(int l=0;l<k-1;++l){
			for(int j=0,t=l;j<k;++j,t=(t+i)%(k-1)){
				if(j==k-1){
					if(c==k-1)c=0,++d;
					printf("%d ",d),++c;
				}else printf("%d ",a[j][t+1]);
			}
			puts("");
		}
	}
}