#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
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
#define mod 1000
struct Matrix{
	int a[8][8];
	Matrix(){ memset(a, 0, sizeof(a)); }
	inline void e(){ rep(i, 0, 7) rep(j, 0, 7) a[i][j] = i == j; }
	int* operator[](const int &k){ return a[k]; }
	inline Matrix operator * (const Matrix&t) const {
		Matrix res;
		rep(i,0,7)rep(j,0,7)rep(k,0,7)(res.a[i][j] += a[i][k] * t.a[k][j]) %= mod;
		return res;
	}
	friend Matrix Matrix_qpow(Matrix a, int k) {
		Matrix res; res.e();
		for(;k;k>>=1,a=a*a)
			if(k&1)res=res*a;
		return res;
	}
} A, B;

signed main(){
	int n = read();
	A[0][0] = 1;
	B[1][0] = B[7][0] = 1;
	B[0][1] = B[2][1] = 1;
	B[1][2] = B[3][2] = 1;
	B[2][3] = 1;
	B[3][4] = B[5][4] = 1;
	B[6][5] = 1;
	B[5][6] = B[7][6] = 1;
	B[0][7] = B[6][7] = 1;
	B = Matrix_qpow(B, n);
	A = A * B;
	printf("%d\n", A[0][4]);
	return 0;
}