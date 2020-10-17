#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int __int128
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int n;
int gcd(int x,int y){return !y?x:gcd(y,x%y);}
struct node{
	int x,y;
	node(int q=0){x=q,y=1;}
	node(int X,int Y){x=X,y=Y;}
	node operator + (const node&t){
		int Y=y/gcd(t.y,y)*t.y;
		int X=x*Y/y+t.x*Y/t.y;
		int g=gcd(X,Y);
		X/=g,Y/=g;
		return node(X,Y);
	}
}ans;
int ws(int x){
	int res=0;
	while(x)x/=10,++res;
	return res;
}
void print(int x,int text=-1){
	int d[40];d[0]=0;
	while(x)d[++d[0]]=x%10,x/=10;
	for(int i=d[0];i;--i)putchar('0'+d[i]);
	if(~text)putchar(text);
}
signed main(){
	signed nnn; std::cin>>nnn;
	n=nnn;
	for(int i=1;i<=n;++i)ans=ans+node(n,i);
	int A=ans.x/ans.y,B=ans.x-A*ans.y;
	if(ans.y==1)return printf("%lld\n",ans.x),0;
	int g=gcd(B,ans.y);
	B/=g,ans.y/=g;
	int l1=ws(A),l2=ws(ans.y);
	for(int i=1;i<=l1;++i)putchar(' ');print(B,'\n');
	print(A);for(int i=1;i<=l2;++i)putchar('-');puts("");
	for(int i=1;i<=l1;++i)putchar(' ');print(ans.y,'\n');
	return 0;
}