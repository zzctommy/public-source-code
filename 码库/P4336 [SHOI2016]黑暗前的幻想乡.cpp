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
const int N=18;
#define mod 1000000007
void fmod(int&x){x+=x>>31&mod,x-=mod,x+=x>>31&mod;}
int n,cnt[1<<N],a[N][N],ans;
vector<pair<int,int> >v[N];
int Gauss(const int&n){
	int res=1;
	rep(i,1,n){
		rep(j,i+1,n){
			while(a[j][i]){
				const int div=a[i][i]/a[j][i];
				rep(k,i,n)fmod(a[i][k]-=1ll*div*a[j][k]%mod),swap(a[i][k],a[j][k]);
				res*=-1;
			}
		}
		if(!a[i][i])return 0;
		res=1ll*res*a[i][i]%mod;
	}
	return fmod(res),res;
}
signed main(){
	n=read();
	rep(i,1,n-1){
		int m=read();
		rep(j,1,m){int x=read(),y=read();v[i].pb(mkp(x,y));}
	}
	rep(msk,1,(1<<(n-1))-1){
		cnt[msk]=cnt[msk>>1]+(msk&1);
		memset(a,0,sizeof(a));
		rep(i,1,n)if(msk>>(i-1)&1){
			rep(j,0,sz(v[i])-1){
				int x=v[i][j].fi,y=v[i][j].se;
				++a[x][x],++a[y][y],--a[x][y],--a[y][x];
			}
		}
		fmod(ans+=1ll*((n-cnt[msk])&1?1:-1)*Gauss(n-1)%mod);
	}
	printf("%d\n",ans);
	return 0;
}