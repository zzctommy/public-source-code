#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
int gcd(int x,int y) {return !y?x:gcd(y,x%y); }
signed main(){
	for (int T = read(); T; -- T) {
		int a = read(), b = read(), k = read(), g = gcd(a, b);
		if (k == 1) {puts("No"); continue; }
		a /= g, b /= g;
		if (a > b) std::swap(a, b);
		if ((b - 2) / a + 1 >= k) puts("No");
		else puts("Yes");
	}
	return 0;
}