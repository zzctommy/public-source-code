#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int k;
string s="codeforces";
signed main(){
	cin>>k;
	if(k==1)return cout<<s<<endl,0;
	int i,j,now=1;
	for(i=1;;++i) {
		now=1;
		for(j=1;j<=10;++j)now*=i;
		if(now>=k)break;
	}
	--i,now=1;
	for(j=1;j<=10;++j)now*=i;
	for(j=1;j<=10;++j){
		now/=i,now*=i+1;
		if(now>=k)break;
	}
	for(int l=1;l<=j;++l)
		for(int k=1;k<=i+1;++k)putchar(s[l-1]);
	for(int l=j+1;l<=10;++l)
		for(int k=1;k<=i;++k)putchar(s[l-1]);
	
}
