#include<bits/stdc++.h>
using namespace std;
string orz(string a,int b)//*
{
	int jw=0,now;
	string ans;
	for(int i=a.length()-1;i>=0;i--)
	{
		now=(a[i]-'0')*b+jw;
		jw=now/10;
		now%=10;
		ans=char(now+'0')+ans;
	}
	while(jw>0)
	{
		char c=jw%10+'0';
		jw/=10;
		ans=c+ans;
	}
	return ans;
} 
string qwq(string a,string b)//+
{
	string ans;
	while(a.length()<b.length())a="0"+a;
	while(b.length()<a.length())b="0"+b;
	int jw=0,now;
	for(int i=a.length()-1;i>=0;i--)
	{
		now=a[i]-'0'+b[i]-'0'+jw;
		jw=now/10;
		now%=10;
		ans=char(now+'0')+ans;
	}
	return ans;
}
int main()
{
	int n;
	ios::sync_with_stdio(false);
	cin>>n;
	string ans,s;
	for(int i=1;i<=n;i++)
	{
		s="1";
		for(int j=1;j<=i;j++)
		{
			s=orz(s,j);
		}
		ans=qwq(ans,s);
	}
	cout<<ans<<endl;
	return 0;
}