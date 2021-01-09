#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=30;
const int M=5e4+5;
int n,sum;
int a[N<<1],dp[N][M*N],flg[N<<1],tmp[2];
vector<int>v;
signed main() {
	n=rd();
	for(rint i=1;i<=(n<<1);++i)a[i]=rd(),sum+=a[i];
	sort(a+1,a+(n<<1)+1);sum-=a[1]+a[2],--n;
	tmp[0]=a[1],tmp[1]=a[2];
	for(rint i=1;i<=(n<<1);++i)a[i]=a[i+2];
	dp[0][0]='F'*'Y'*'Y'*'A'*'K'*'I'*'O'*'I';
	for(rint i=1;i<=(n<<1);++i) {
		for(rint j=1,mx=min(i,n);j<=mx;++j) {
			for(rint k=a[i];k<=sum;++k) {
				if(dp[j][k])continue;
				if(dp[j-1][k-a[i]]&&dp[j-1][k-a[i]]!=i)dp[j][k]=i;
			}
		}
	}
	for(rint i=sum>>1;i>=0;--i) {
		if(!dp[n][i])continue;
		int now=i;
		for(rint j=n;j>=1;--j)
			v.pb(a[dp[j][now]]),flg[dp[j][now]]=1,now-=a[dp[j][now]];
		break;
	}
	sort(v.begin(),v.end());
	printf("%d",tmp[0]);for(uint i=0;i<v.size();++i)printf(" %d",v[i]);puts("");
	for(rint i=(n<<1);i>=1;--i)if(!flg[i])printf("%d ",a[i]);printf("%d\n",tmp[1]);
	return 0;
}