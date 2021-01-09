#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
#define F(i,l,r) for(int i=l;i<=r;++i)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
inline int rdc() {
    char ch=getchar();
    while(!isdigit(ch))ch=getchar();
    return ch-'0';
}
const int mod=2009;
int n,t,m;
struct Maxtrix {
    int a[99][99];
    int*operator[](const int&k){return a[k];}
	Maxtrix(){memset(a,0,sizeof(a));}
}mp,res,tmp;
int f(int x,int y){return x+y*n;}
signed main() {
    m=(n=rd())*9,t=rd();
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=8;++j)
			mp[f(i,j)][f(i,j-1)]=1;
		for(int j=1;j<=n;++j) {
			int w=rdc();
			if(w)mp[i][f(j,w-1)]=1;
		}
	}
    res=mp,--t;
    while(t) {
        if(t&1){
			F(i,1,m)F(j,1,m)tmp[i][j]=0;
			F(i,1,m)F(k,1,m)F(j,1,m)tmp[i][j]=(tmp[i][j]+res[i][k]*mp[k][j])%mod;
			res=tmp;
		}
		F(i,1,m)F(j,1,m)tmp[i][j]=0;
        F(i,1,m)F(k,1,m)F(j,1,m)tmp[i][j]=(tmp[i][j]+mp[i][k]*mp[k][j])%mod;
		mp=tmp;
        t>>=1;
    }
    printf("%d\n",res[1][n]);
    return 0;
}