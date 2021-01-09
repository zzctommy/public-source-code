//#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
#define int long long
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return x*f;
}
const int N=1e5+10;
int a[3][N],T,ans,len[3],mx[3];
int p2(int x) {return x*x;}
int calc(int x,int y,int z) {
	return p2(x-y)+p2(y-z)+p2(z-x);
}
signed main() {
	T=rd();
	while(T--) {
		ans=4e18;mx[0]=mx[1]=mx[2]=0;
		len[0]=rd(),len[1]=rd(),len[2]=rd();
		for(rint i=0;i<3;++i)
			for(rint j=1;j<=len[i];++j)
				a[i][j]=rd();
		sort(a[0]+1,a[0]+len[0]+1),sort(a[1]+1,a[1]+len[1]+1),sort(a[2]+1,a[2]+len[2]+1);
		for(rint i=0;i<3;++i) {
			for(rint j=0;j<3;++j) {
				if(i==j)continue;
				for(rint k=0;k<3;++k) {
					if(k==i||k==j)continue;
					for(rint l=1;l<=len[i];++l) {
						int Y=lower_bound(a[j],a[j]+len[j]+1,a[i][l])-a[j];
						int Z=upper_bound(a[k],a[k]+len[k]+1,a[i][l])-a[k];
						if(Y!=len[j]+1&&Z!=1) ans=min(ans,calc(a[i][l],a[j][Y],a[k][--Z]));
					}
				}
			}
		}
		printf("%lld\n",ans);
		for(rint i=0;i<3;++i)
			for(rint j=1;j<=len[i];++j)
				a[i][j]=0;
	}
	return 0;
}