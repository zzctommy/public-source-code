//Orz cyn2006
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=800005;
int n,k,l[N];
LL sum,d[N];
signed main(){
	n=read(),k=read(),sum=1;
	rep(i,1,n)l[i]=read(),sum+=l[i];
	sort(l+1,l+n+1,greater<int>()),sum-=n<<1;
	if(sum<k)return puts("-1"),0;
	int it=1;d[0]=1,d[1]=-1,sum=0;
	for(int i=0;"fyy AK IOI";++i){
		sum+=d[i],d[i+1]+=d[i];
		if(sum+d[i+1]>=k)return printf("%d\n",i+1),0;
		for(;d[i]>0&&it<=n;++it){
			int l1=(l[it]-1)/2,l2=l[it]-1-l1;
			d[i+2]+=2,--d[i+2+l1],--d[i+2+l2],--d[i],--sum;
		}
	}
	assert(0);
}