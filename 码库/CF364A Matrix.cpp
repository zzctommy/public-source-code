//Orz cyn2006
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
const int N=4005;
unordered_map<int,int>mp;
int a,n;
LL ans;
char str[N];
signed main(){
	scanf("%d%s",&a,str+1),n=strlen(str+1);
	for(int i=1;i<=n;++i){
		int sum=0;
		for(int j=i;j<=n;++j){
			sum+=str[j]-'0';
			if(!a&&!sum)++mp[0];
			else if(sum&&a%sum==0)++mp[sum];
		}
	}
	for(int i=1;i<=n;++i){
		int sum=0;
		for(int j=i;j<=n;++j){
			sum+=str[j]-'0';
			if(!a&&!sum)ans+=n*(n+1)/2-mp[0];
			else if(sum&&a%sum==0)ans+=mp[a/sum];
		}
	}
	if(!a)ans+=1ll*mp[0]*mp[0];
	printf("%lld\n",ans);
	return 0;
}