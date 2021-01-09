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
#define per(i,y,x) for(int i=y,i##end=x;i>=i##end;--i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
#define N 100005

int n,m,a[N],stk[N],top,mu[N],pri[N/10],pct,b[N],c[N],cnt[N];
LL ans;
bool vis[N];
vector<int>d[N];
void init(){
	mu[1]=1;
	rep(i,2,m){
		if(!vis[i])pri[++pct]=i,mu[i]=-1;
		for(int j=1;j<=pct&&i*pri[j]<N;++j){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0){mu[i*pri[j]]=0;break;}
			mu[i*pri[j]]=-mu[i];
		}
	}
	for(int i=1;i<=m;++i)
		for(int j=1;i*j<=m;++j)
			d[i*j].pb(i);
}
void upd(int x){
	rep(i,0,sz(d[x])-1)++c[d[x][i]];
}
void del(int x){
	rep(i,0,sz(d[x])-1)--c[d[x][i]];
}
int calc(int x){
	int res=0;
	rep(i,0,sz(d[x])-1)
		res+=mu[d[x][i]]*c[d[x][i]];
	return res;
}
signed main(){
	n=read();
	rep(i,1,n)a[i]=read(),ckmax(m,a[i]),++cnt[a[i]];
	sort(a+1,a+n+1,greater<int>());
	init();
	rep(t,1,m){
		b[0]=0;
		for(int i=1;i*t<=m;++i)
			rep(j,1,cnt[i*t])b[++b[0]]=i;
		reverse(b+1,b+b[0]+1);
		rep(i,1,b[0]){
			int now=calc(b[i]);
			while(now>=1){
				if(__gcd(stk[top],b[i])==1){
					if(now==1)break;
					else --now;
				}
				del(stk[top]),--top;
			}
			if(now==1)ckmax(ans,1ll*b[i]*stk[top]*t);
			stk[++top]=b[i],upd(b[i]);
		}
		while(top)del(stk[top--]);
	}
	printf("%lld\n",ans);
}