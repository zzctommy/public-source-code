#include<bits/stdc++.h>
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
typedef long long LL;
const int N=4005;
const LL inf=1e11;
int n,k,s[N][N],a[N][N],g[N];
LL f[N],ANS,ans;
int check(int m){
	for(int i=1;i<=n;++i){
		f[i]=inf;
		for(int j=0;j<i;++j){
			LL pre=f[j]+s[j+1][i]+m;
			// std::cerr<<j<<' '<<pre<<' '<<f[j]<<' '<<g[j]<<'\n';
			if(pre<f[i])f[i]=pre,g[i]=g[j]+1;
			else if(pre==f[i]&&g[j]+1<g[i])g[i]=g[j]+1;
		}
		// std::cerr<<i<<' '<<f[i]<<' '<<g[i]<<'\n';
	}
	return ANS=f[n],g[n];
}
signed main(){
	n=read(),k=read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			a[i][j]=read()+a[i][j-1];
	// for(int i=1;i<=n;++i){
		// for(int j=1;j<=n;++j)std::cerr<<a[i][j]<<' ';
		// std::cerr<<'\n';
	// }
	// puts("---------------");
	for(int i=1;i<=n;++i)
		for(int j=i;j<=n;++j)
			s[i][j]=s[i][j-1]+a[j][j]-a[j][i-1];
	// for(int i=1;i<=n;++i){
		// for(int j=1;j<=n;++j)std::cerr<<s[i][j]<<' ';
		// std::cerr<<'\n';
	// }
	// puts("---------------");
	// for(int i=1;i<=n;++i)std::cerr<<f[i]<<' ';std::cerr<<'\n';
	// for(int i=1;i<=n;++i)std::cerr<<g[i]<<' ';std::cerr<<'\n';
	int l=0,r=s[1][n];
	while(l<=r){
		int mid=(l+r)>>1,m=check(mid);
		// std::cerr<<mid<<' '<<m<<' '<<ANS<<'\n';
		if(m<=k)ans=ANS-1ll*k*mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",ans);
	return 0;
}