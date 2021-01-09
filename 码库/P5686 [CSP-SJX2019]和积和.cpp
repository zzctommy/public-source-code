#include<bits/stdc++.h>
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=500005;
const int mod=1e9+7;
int fmod(int&x){x-=mod,x+=x>>31&mod;}
int n,a[N],b[N];
int ans[N],sa,sb,lst,sum;
signed main(){
	n=read();
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<=n;++i)b[i]=read();
	for(int i=1;i<=n;++i){
		fmod(ans[i]+=1ll*a[i]*b[i]%mod*i%mod);
		fmod(ans[i]+=1ll*a[i]*sb%mod);
		fmod(ans[i]+=1ll*b[i]*sa%mod);
		fmod(sa+=1ll*i*a[i]%mod),fmod(sb+=1ll*i*b[i]%mod);
		fmod(ans[i]+=ans[i-1]);
	}
	for(int i=1;i<=n;++i)fmod(sum+=ans[i]);
	printf("%d\n",sum);
	return 0;
}