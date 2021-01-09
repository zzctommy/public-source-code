#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=200009;
int n,k,a[N];
char s[N];
signed main() {
	n=rd(),k=rd(),scanf("%s",s+1);
	int flg=1;
	for(int i=1;i<=n;++i)a[i]=s[i]-'0';
	for(int i=1;i<=n;++i) {
		if(a[(i-1)%k+1]<s[i]-'0'){flg=0;break;}
		else if(a[(i-1)%k+1]>s[i]-'0')break;
	}
	if(flg){
		printf("%d\n",n);
		for(int i=1;i<=n;++i)printf("%d",a[(i-1)%k+1]);
		return 0;
	}
	++a[k];
	for(int i=k;i>=1;--i)
		if(a[i]==10)a[i]=0,++a[i-1];
		else break;
	printf("%d\n",n);
	for(int i=1;i<=n;++i)printf("%d",a[(i-1)%k+1]);
	return 0;
}