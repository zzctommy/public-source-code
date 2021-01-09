#include<bits/stdc++.h>
using namespace std;
#define int long long
int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int n,mod,k;
struct Matrix {
	int a[3][3];
	Matrix(){memset(a,0,sizeof(a));}
	void clear(){*this=Matrix();}
	void e(){
		for(int i=0;i<3;++i)
			for(int j=0;j<3;++j)
				a[i][j]=(i==j);
	}
	void Start() {
		a[0][0]=0,a[0][1]=0,a[0][2]=0,
		a[1][0]=1,a[1][1]=0,a[1][2]=0,
		a[2][0]=1,a[2][1]=0,a[2][2]=0;
	}
	void make(int x=1) {
		a[0][0]=x%mod,a[0][1]=1,a[0][2]=0,
		a[1][0]=0,a[1][1]=1,a[1][2]=1,
		a[2][0]=0,a[2][1]=0,a[2][2]=1;
	}
	int*operator[](const int &k){return a[k];}
	Matrix operator * (const Matrix &t) {
		Matrix res;
		for(int i=0;i<3;++i)
			for(int k=0;k<3;++k)
				for(int j=0;j<3;++j)
					res.a[i][j]=(res.a[i][j]+a[i][k]*t.a[k][j]%mod)%mod;
		return res;
	}
	Matrix operator ^ (int k) {
		Matrix res,n=*this;res.e();
		while(k) {
			if(k&1)res=res*n;
			n=n*n,k>>=1;
		}
		return res;
	}
}ans;
void calc(int x,int y) {
	Matrix p;p.make(x);
	ans=(p^y)*ans;
}
signed main() {
	n=rd(),mod=rd(),ans.Start();
	for(int i=10,j=0;j<n;i*=10)
		calc(i,min(n,i-1)-j),j=min(n,i-1);
	printf("%lld\n",ans[0][0]);
	return 0;
}
