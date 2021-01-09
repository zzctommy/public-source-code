#include<bits/stdc++.h>
using namespace std;
#define rint register int
#define N 85
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
string plu(string a,string b) {
	string res="";
	while(a.length()<b.length())a='0'+a;
	while(b.length()<a.length())b='0'+b;
	int jw=0,tmp=0;
	for(rint i=a.length()-1;i>=0;--i) {
		tmp=jw+a[i]-'0'+b[i]-'0';
		jw=tmp/10,tmp%=10;
		res=(char)(tmp+'0')+res;
	}
	if(jw)res=(char)(jw+'0')+res;
	return res;
}
int x[45],y[45];
string mul(string a,int b) {
	string res="";
	memset(x,0,sizeof(x));
	memset(y,0,sizeof(y));
	int jw=0;
	for(rint i=a.length()-1;i>=0;--i)
		x[i]=a[a.length()-i-1]-'0';
	for(rint i=0;i<a.length();++i) {
		y[i]=b*x[i]+jw;
		jw=y[i]/10,y[i]%=10;
	}
	int top=a.length()-1;
	while(jw>0)y[++top]=jw%10,jw/=10;
	while(!y[top]&&top>=1)--top;
	for(rint i=0;i<=top;++i)
		res=(char)(y[i]+'0')+res;
	return res;
}
string max(string a,string b) {
	if(a.length()<b.length())return b;
	if(a.length()>b.length())return a;
	for(rint i=0;i<a.length();++i)
		if(a[i]^b[i])return a[i]<b[i]?b:a;
	return a;
}
int n,m;
string bin[N],ans="0",dp[N][N];
int a[N];
int main() {
	n=rd(),m=rd();
	bin[0]="1";for(rint i=1;i<=m;++i)bin[i]=mul(bin[i-1],2);
	while(n--) {
		for(rint i=1;i<=m;++i)a[i]=rd();
		for(rint i=1;i<=m;++i)
			for(rint j=1;j<=m;++j)
				dp[i][j]="0";
		for(rint i=1;i<=m;++i)
			for(rint j=m;j>=i;--j) {
				dp[i][j]="0";
				dp[i][j]=max(dp[i][j],plu(dp[i-1][j],mul(bin[m-j+i-1],a[i-1])));
				dp[i][j]=max(dp[i][j],plu(dp[i][j+1],mul(bin[m-j+i-1],a[j+1])));
			}
		string tmp="0";
		for(rint i=1;i<=m;++i)
			tmp=max(tmp,plu(dp[i][i],mul(bin[m],a[i])));
		ans=plu(ans,tmp);
	}
	cout<<ans<<endl;
	return 0;
} 