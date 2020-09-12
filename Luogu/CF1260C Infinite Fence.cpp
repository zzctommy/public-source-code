#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,r,b,k;
signed main() {
	scanf("%lld",&n);
	while(n--) {
		scanf("%lld%lld%lld",&r,&b,&k);
		if(r>b)swap(r,b);
		int GCD=__gcd(r,b);
		r/=GCD,b/=GCD;
		if(r*(k-1)+1>=b) puts("OBEY");
		else puts("REBEL");
	}
	return 0;
}