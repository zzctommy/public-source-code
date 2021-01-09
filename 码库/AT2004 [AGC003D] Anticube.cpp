#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef long double db;
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
const int N=100005;
int n,ans;
int pct,pri[N];
bool vis[N];
LL a[N];
map<LL,LL>to;
map<LL,int>num;
void Sieve(const int&n){
	for(int i=2;i<=n;++i){
		if(!vis[i])pri[++pct]=i;
		for(int j=1;j<=pct&&i*pri[j]<=n;++j){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0)break;
		}
	}
}
void insert(LL x){
	static int cnt_1=0;
	LL pre=x,iv=1;
	for(int i=1;i<=pct;++i){
		if(pri[i]>2155)break;
		if(x%pri[i])continue;
		LL tmp=1ll*pri[i]*pri[i]*pri[i];
		while(x%tmp==0)x/=tmp,pre/=tmp;
		if(x%pri[i])continue;
		while(x%pri[i]==0)x/=pri[i],tmp/=pri[i];
		iv*=tmp;
	}
	if(x>100000){
		LL tmp=sqrt(x);
		if(tmp*tmp==x)iv*=tmp;
		else iv=-1;
	}else{
		iv*=x*x;
	}
	if(pre>1)to[pre]=iv,++num[pre];
	else ans+=cnt_1^1,cnt_1=1;
}
signed main(){
	scanf("%d",&n);
	Sieve(100000);
	rep(i,1,n)scanf("%lld",&a[i]),insert(a[i]);
	for(auto i:to){
		if(num[i.first]>=num[i.second])ans+=num[i.first],num[i.second]=0;
	}
	printf("%d\n",ans);
	return 0;
}