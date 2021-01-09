#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
int A,B,C,D;
LL ans;
signed main() {
	A=rd(),B=rd(),C=rd(),D=rd();
	for(int i=max(A+B,C+1);i<=B+C;++i) {
		int x=min(B,i-B)-max(A,i-C)+1;
		int z=min(i-1,D)-C+1;
		ans+=1ll*x*z;
	}
	cout<<ans<<endl;
}