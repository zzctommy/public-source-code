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

#define mod 1000000007
void fmod(int&x){x-=mod,x+=x>>31&mod;}
int n,L,m,v[3][1000000],ans;
struct Matrix{
	int a[100][100];
	Matrix(){memset(a,0,sizeof(a));}
	void e(){rep(i,0,m-1)rep(j,0,m-1)a[i][j]=i==j;}
	int*operator[](const int&k){return a[k];}
	inline Matrix operator*(const Matrix&b){
		Matrix res;
		rep(i,0,m-1)rep(j,0,m-1)rep(k,0,m-1)fmod(res.a[i][j]+=1ll*a[i][k]*b.a[k][j]%mod);
		return res;
	}
	void print(){
		rep(i,0,m-1)rep(j,0,m-1)printf("%d%c",a[i][j]," \n"[j==m-1]);
	}
}sta,tur;
inline Matrix Matrix_pow(Matrix n,int k){
	if(!k){
		Matrix qwq;qwq.e();return qwq;
	}
	Matrix res=n;--k;
	for(;k;k>>=1,n=n*n)if(k&1)res=res*n;
	return res;
}
signed main(){
	n=read(),L=read(),m=read();
	rep(i,0,2)rep(j,0,n-1)v[i][j]=read()%m;
	rep(i,0,n-1)++sta[0][v[0][i]%m];
	rep(i,0,n-1)rep(j,0,m-1)++tur[j][(v[1][i]+j)%m];
//	sta.print(),tur.print();
	sta=sta*Matrix_pow(tur,L-2);
//	sta.print();
	rep(i,0,n-1)
		fmod(ans+=sta[0][(2*m-v[2][i]-v[1][i])%m]);
	printf("%d\n",ans);
	return 0;
}