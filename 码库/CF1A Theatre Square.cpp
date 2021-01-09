#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll chenzhe(ll a,ll b)
{
	if(a%b==0)return a/b;
	return a/b+1;
}
int main()
{
	ll n,m,a;
	cin>>n>>m>>a;
	ll kkk=chenzhe(n,a),sc03=chenzhe(m,a);
	cout<<kkk*sc03<<endl;
	return 0;
}