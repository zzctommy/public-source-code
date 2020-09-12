#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a=1,t,k;
	cin>>k;
	while((a+1)*a/2<k)
	{
		a++;
	}
	a--;
	t=k-a*(a+1)/2;
	a++;
	if(a%2==1)cout<<a+1-t<<"/"<<t<<endl;
	else cout<<t<<"/"<<a+1-t<<endl;
	return 0;
}