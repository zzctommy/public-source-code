#include<bits/stdc++.h>
#define ll long long
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define _rep(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define mod 998244353
typedef std::pair<int,int> pii;
inline int upd(const int x){return x+(x>>31&mod);}
inline void reduce(int&x){x-=mod,x+=x>>31&mod;}
inline void add(int&x,const int y){x=upd((x+y)%mod);}
#define N 200005

int n,m,a[N],b[N],ans,lst[N];
std::map<int,int>mp;
int main(){
	std::ios::sync_with_stdio(0);
	std::cin.tie(0),std::cout.tie(0);
	std::cin>>n>>m;
	rep(i,1,n) std::cin>>a[i];
	rep(i,1,m) std::cin>>b[i],mp[b[i]]=i;
	rep(i,1,n) if(mp[a[i]])lst[mp[a[i]]]=i;
	ans=1;
	rep(i,1,m){
		int j=lst[i];
		for(;j>=lst[i-1];--j) if(a[j]<a[lst[i]])break;
		if(i==1)ans*=!j;
		else {
			ans=1ll*ans*(lst[i]-j)%mod;
			rep(j,lst[i-1],lst[i]) if(a[j]<a[lst[i-1]])return std::cout<<"0\n",0;
		}
	}
	rep(i,lst[m],n)if(a[i]<a[lst[m]])return std::cout<<"0\n",0;
	std::cout<<ans<<'\n';
}