#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100010;
int T;
char s[N],t[N],a[4]="abc";
signed main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%s",s+1);int n=strlen(s+1);
		t[0]=s[0]='#',t[n+1]=s[n+1]='#';
		for(rint i=1;i<=n;++i) {
			if(s[i]!='?')t[i]=s[i];
			else {
				for(rint j=0;j<3;++j)
					if(a[j]!=t[i-1]&&a[j]!=s[i+1]){t[i]=a[j];break;}
			}
		}
		int flg=0;
		for(rint i=2;i<=n;++i)if(t[i]==t[i-1]){flg=1;break;}
		if(flg){puts("-1");continue;}
		for(rint i=1;i<=n;++i)putchar(t[i]);puts("");
	}
	return 0;
}