#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=100010;
int a[N],m,l,r,n,q;
unordered_map<int,int>mp;
int phi(int x) {
	int tmp=x;
	if(mp.count(x))return mp[x];
	int res=x;
	for(int i=2; i*i<=x; ++i) {
		if(x%i==0) {
			res=res-res/i;
			while(x%i==0)x/=i;
		}
	}
	if(x>1)res=res-res/x;
	return mp[tmp]=res;
}
int mod(int x,int m) {
	return x>=m?x%m+m:x;
}
int qpow(int n,int k,int p) {
	int base=n,res=1;
	while(k) {
		if(k&1)res=mod(res*base,p);
		base=mod(base*base,p);
		k>>=1;
	}
	return res;
}
int f(int l,int r,int m) {
	if(l==r||m==1)return mod(a[r],m);
	return qpow(a[l],f(l+1,r,phi(m)),m);
}
signed main() {
	scanf("%lld%lld",&n,&m);
	for(int i=1; i<=n; ++i)scanf("%lld",&a[i]);
	scanf("%lld",&q);
	while(q--) {
		scanf("%lld%lld",&l,&r);
		printf("%lld\n",f(l,r,m)%m);
	}
	return 0;
}