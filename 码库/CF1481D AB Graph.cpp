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
const int N=1005;
int n,m;
char mp[N][N];
void Main(){
	n=read(),m=read();
	rep(i,1,n)scanf("%s",mp[i]+1);
	if(m&1){
		puts("YES");
		rep(j,0,m)printf("%d ",j&1?1:2);
		puts("");
		return;
	}
	rep(i,1,n){
		rep(j,1,n){
			if(i==j)continue;
			if(mp[i][j]==mp[j][i]){
				puts("YES");
				rep(k,0,m)printf("%d ",k&1?i:j);
				puts("");
				return;
			}
		}
	}
	rep(i,1,n){
		int in[2],ou[2],x=0,y=0;
		memset(in,0,sizeof(in)),memset(ou,0,sizeof(ou));
		rep(j,1,n){
			if(i==j)continue;
			if(mp[i][j]=='a')ou[0]=j;
			else ou[1]=j;
			if(mp[j][i]=='a')in[0]=j;
			else in[1]=j;
		}
		if(in[0]&&ou[0])x=in[0],y=ou[0];
		else if(in[1]&&ou[1])x=in[1],y=ou[1];
		if(!x||!y)continue;
		puts("YES");
		rep(j,1,m/2)
			if(m/2%2!=j%2)printf("%d ",i);
			else printf("%d ",in[0]);
		printf("%d ",i);
		rep(j,m/2+2,m+1)
			if(m/2%2!=j%2)printf("%d ",i);
			else printf("%d ",ou[0]);
		puts("");
		return;
	}
	puts("NO");
}
signed main(){for(int T=read();T;--T)Main();}