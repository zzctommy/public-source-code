#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define x first
#define y second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 1000005
int n,P[N];
char str[N];
LL ans;
signed main(){
	scanf("%d%s",&n,str);
	int j=-1;P[0]=-1;
	for(int i=1;i<n;++i){
		while(~j&&str[j+1]!=str[i])j=P[j];
		if(str[j+1]==str[i])++j;
		P[i]=j;
	}
	for(int i=0;i<n;++i){
		j=P[i];
		while(~j&&~P[j])P[i]=j=P[j];
		if(~j)ans+=i-j;
	}
	printf("%lld\n",ans);
	return 0;
}