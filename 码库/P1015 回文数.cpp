#include<bits/stdc++.h>
using namespace std;
int n;
string s;
bool isp(string s)
{
	if(s[0]==0)return false;
	for(int i=0;i<s.length()/2;i++)
	{
		if(s[i]!=s[s.length()-i-1])return false;
	}
	return true;
}
string sswap(string s)
{
	for(int i=0;i<s.length()/2;i++)
	{
		swap(s[i],s[s.length()-i-1]);
	}
	return s;
}
string pplus(string a,string b)
{
	string ans;
	while(a.length()<b.length())a="0"+a;
	while(a.length()>b.length())b="0"+b;
	int jw=0,now=0,aa,bb;
	for(int i=a.length()-1;i>=0;i--)
	{
		if(a[i]>='0'&&a[i]<='9')aa=a[i]-'0';
		else aa=a[i]-'A'+10;
		if(b[i]>='0'&&b[i]<='9')bb=b[i]-'0';
		else bb=b[i]-'A'+10;
		now=aa+bb+jw;
		jw=now/n;
		now%=n;
		if(now<10)ans=char('0'+now)+ans;
		else ans=char(now-10+'A')+ans;
	}
	if(jw>0)ans=char(jw+'0')+ans;
	return ans;
}
int main()
{
	
	ios::sync_with_stdio(false);
	cin>>n>>s;
	for(int i=0;i<=30;i++)
	{
		if(isp(s)){printf("STEP=%d\n",i);return 0;}
		s=pplus(s,sswap(s));
	}
	puts("Impossible!");
	return 0;
}