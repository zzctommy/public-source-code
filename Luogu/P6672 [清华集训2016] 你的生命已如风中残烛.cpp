#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n,w[45],m,cynAK=1;
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&w[i]),m+=w[i];
	for(int i=1;i<=m;++i)if(m-n+1!=i)cynAK=1ll*cynAK*i%mod;
	std::cout<<cynAK<<'\n';
}