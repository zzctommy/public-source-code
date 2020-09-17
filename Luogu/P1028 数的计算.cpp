#include<bits/stdc++.h>
using namespace std;
int main() {
	int n,f[1005]={0};
	cin>>n;
	for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=i/2;j++)
				f[i]+=f[j];
			f[i]++;
		}
	cout<<f[n]<<endl;
	return 0;
}
