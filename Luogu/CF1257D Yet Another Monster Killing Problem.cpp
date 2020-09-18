#include<bits/stdc++.h>
using namespace std;
#define pb(x) push_back(x)
typedef long long LL;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=200005;
int n,m,a[N],mx[N],ans,p[N],s[N];
void Main(){
	n=read(),ans=0;
	for(int i=1;i<=n;++i)a[i]=read(),mx[i]=0;
	m=read();
	for(int i=1;i<=m;++i)p[i]=read(),s[i]=read(),mx[s[i]]=max(p[i],mx[s[i]]);
	for(int i=n-1;i>=1;--i)mx[i]=max(mx[i+1],mx[i]);
	for(int i=1,cnt=0,now=0;i<=n;++i){
		if(a[i]>mx[1])return puts("-1"),void();
		++cnt,now=max(now,a[i]);
		if(mx[cnt]<now)++ans,cnt=1,now=a[i];
	}
	printf("%d\n",ans+1);
}
signed main(){
	for(int T=read();T;--T)Main();
}
