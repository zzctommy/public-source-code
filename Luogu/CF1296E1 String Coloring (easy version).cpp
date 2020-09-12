#include<bits/stdc++.h>
using namespace std;
int l0,l1,n;
string ans,s;
int main()
{
	cin>>n>>s;
	for(int i=0;i<n;++i)
	{
		if(s[i]>=l0)ans+='0',l0=s[i];
		else if(s[i]>=l1)ans+='1',l1=s[i];
		else return puts("NO"),0;
	}
	puts("YES");cout<<ans<<endl;
	return 0;
}