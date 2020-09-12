#include<bits/stdc++.h>
using namespace std;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
map<string,string>mp;
map<string,bool>mp2;
int n,m;
signed main() {
	mp["purple"]="Power";
	mp["green"]="Time";
	mp["blue"]="Space";
	mp["orange"]="Soul";
	mp["red"]="Reality";
	mp["yellow"]="Mind";
	n=rd(),m=6;
	string s;
	for(int i=1;i<=n;++i)cin>>s,mp2[s]=1,--m;
	cout<<m<<endl;
	for(auto i:mp)if(!mp2[i.first])cout<<i.second<<endl;
	return 0;
}