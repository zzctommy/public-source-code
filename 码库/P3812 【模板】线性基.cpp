#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<vector>
#include<iostream>
#include<cmath>
using std::cout;
using std::endl;
using std::vector;
using std::lower_bound;
using std::unique;
using std::sort;
using std::max;
using std::min;
#define int long long
inline int rd(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch))f=(ch=='-'?0:f),ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}

#define N 50009
#define T (N<<2)
#define A 50

//LinearBase
struct LinearBase {
	int d[A+1];
	LinearBase(){memset(d,0,sizeof(d));}
	void insert(int x) {
		for(int i=A;~i;--i)
			if(x>>i&1) {
				if(d[i])x^=d[i];
				else return d[i]=x,void();
			}
	}
	int query(int x) {
		for(int i=A;~i;--i)x=max(x,x^d[i]);
		return x;
	}
	void reset() {
		*this=LinearBase();
	}
}lb;
signed main() {
    int n=rd();
    for(int i=1;i<=n;++i)lb.insert(rd());
    printf("%lld\n",lb.query(0));
    return 0;
}