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
int f[1<<20],n,c[30],m,mp[20][20],a[100005];
char str[100005];
int calc(int msk,int x){
	int res=mp[x][x];
	for(int i=0;i<m;++i)if(msk>>i&1)
		res+=mp[x][i];
	return res;
}
signed main(){
	scanf("%s",str+1),n=strlen(str+1);
	rep(i,1,n)a[i]=str[i]-'a';
	memset(c,-1,sizeof(c));
	for(int i=1;i<=n;++i){
		if(!~c[a[i]])c[a[i]]=m++;
		if(i>1)++mp[c[a[i-1]]][c[a[i]]];
	}
	//rep(i,1,n)cerr<<c[a[i]]<<' ';cerr<<'\n';
	memset(f,0x3f,sizeof(f));
	f[0]=1;
	for(int msk=0;msk<1<<m;++msk){
		for(int i=0;i<m;++i){
			if(msk>>i&1)continue;
			ckmin(f[msk|(1<<i)],f[msk]+calc(msk,i));
		}
	}
	printf("%d\n",f[(1<<m)-1]);
	return 0;
}