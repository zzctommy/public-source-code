#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return x*f;
}
const int N=50010;
int n,D;
LL ans[5];
char s[N][5];
signed main() {
	n=rd(),D=rd();
	for(rint i=1;i<=n;++i)scanf("%s",s[i]);
	for(rint mask=0;mask<16;++mask) {
		int cnt=0;map<int,int>mp;
		LL sum=0;
		for(rint j=0;j<4;++j)
			if((mask>>j)&1)++cnt;
		for(rint i=1;i<=n;++i) {
			int h=0;
			for(rint j=0;j<4;++j)
				if((mask>>j)&1)h=h*131+'*';
				else h=h*131+s[i][j];
			sum+=mp[h],++mp[h];
		}
		ans[cnt]+=sum;
	}
	ans[1]-=ans[0];
	ans[2]-=ans[0]+3*ans[1];
	ans[3]-=ans[0]+3*ans[1]+2*ans[2];
	ans[4]-=ans[0]+ans[1]+ans[2]+ans[3];
	printf("%lld\n",ans[D]);
	return 0;
}
