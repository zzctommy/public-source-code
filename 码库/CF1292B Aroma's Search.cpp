#include<bits/stdc++.h>
using namespace std;
#define int long long
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
const int inf=1e16+20;
int ax,ay,bx,by,t,sx,sy;
int x[70],y[70],cnt,ans;
int dis(int xx,int yy,int xxx,int yyy) {
	return abs(xx-xxx)+abs(yy-yyy);
}
int f(int i,int j) {
	if(i>j)return 0;
	int res=0;
	for(rint k=i+1;k<=j;++k)res+=dis(x[k-1],y[k-1],x[k],y[k]);
	return res;
}
signed main() {
	scanf("%lld%lld%lld%lld%lld%lld%lld%lld%lld",&x[1],&y[1],&ax,&ay,&bx,&by,&sx,&sy,&t);cnt=1;
	while(1) {
		++cnt,x[cnt]=ax*x[cnt-1]+bx,y[cnt]=ay*y[cnt-1]+by;
		if(x[cnt]>inf||y[cnt]>inf) {break;}
	}
	for(rint i=1;i<=cnt;++i) {
		int tmp=0,j,sum=0;
		tmp+=dis(x[i],y[i],sx,sy);
		if(tmp>t)continue;
		for(j=1;j<=i;++j)if(f(j,i)+tmp<=t)break;
		tmp+=f(j,i);
		sum=i-j+1;
		ans=max(sum,ans);
//		cout<<i<<' '<<j<<' ';
		if(j==1) {
			tmp+=f(1,i);
			if(tmp>t)continue;
			for(j=i+1;j<=cnt;++j)if(tmp+f(i,j)>t)break;
			--j;
			sum+=j-i;
			ans=max(ans,sum);
		}
//		cout<<j<<endl;
//		printf("%lld\n",ans);
	} 
	printf("%lld\n",ans);
	return 0;
}