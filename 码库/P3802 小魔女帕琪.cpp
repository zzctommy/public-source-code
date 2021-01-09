#include<bits/stdc++.h>
using namespace std;
double cynAK=5040;
int n,a[7];
signed main(){
	for(int i=0;i<7;++i)std::cin>>a[i],n+=a[i];
	for(int i=0;i<7;++i)
		if(i<6)cynAK*=1.*a[i]/(n-i);
		else cynAK*=a[i];
	printf("%.3lf\n",cynAK);
	return 0;
}