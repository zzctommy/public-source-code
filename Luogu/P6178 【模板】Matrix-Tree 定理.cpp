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
const int N=305;
#define mod 1000000007
void fmod(int&x){x+=x>>31&mod,x-=mod,x+=x>>31&mod;}
int n,m,t,a[N][N],ans=1;
void Gauss(){
	rep(i,2,n){
		rep(j,i+1,n){
			while(a[j][i]){
				int div=a[i][i]/a[j][i];
				rep(k,i,n)fmod(a[i][k]-=1ll*div*a[j][k]%mod),swap(a[i][k],a[j][k]);
				ans*=-1;
			}
		}
	}
}
signed main(){
	n=read(),m=read(),t=read();
	rep(i,1,m){
		int x=read(),y=read(),z=read();
		if(!t){
			fmod(a[x][x]+=z),fmod(a[y][y]+=z);
			fmod(a[x][y]-=z),fmod(a[y][x]-=z);
		}else{
			fmod(a[y][y]+=z),fmod(a[x][y]-=z);
		}
	}
	//rep(i,1,n)rep(j,1,n)printf("%-10d%c",a[i][j]," \n"[j==n]);
	Gauss();
	//rep(i,1,n)rep(j,1,n)printf("%-10d%c",a[i][j]," \n"[j==n]);
	rep(i,2,n)ans=1ll*ans*a[i][i]%mod;
	fmod(ans);
	printf("%d\n",ans);
	return 0;
}