#include<bits/stdc++.h>
#define int long long
using std::cout;
using std::endl;
inline int rd(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch))f=(ch=='-'?0:f),ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
int n,m,ans;
int calc_w(int a,int b,int c,int d) {
	if(a>c||b>d)return 0;
	int n1=(c-a+1)/2+((c-a+1)&1?(a&1):0),n2=c-a+1-n1;
	int n3=(d-b+1)/2+((d-b+1)&1?(b&1):0),n4=d-b+1-n3;
	// cout<<n1<<' '<<n2<<' '<<n3<<' '<<n4<<endl;
	return n1*n3+n2*n4;
}
int calc_s(int a,int b,int c,int d) {
	if(a>c||b>d)return 0;
	return (c-a+1)*(d-b+1);
}
int calc_b(int a,int b,int c,int d) {
	if(a>c||b>d)return 0;
	return calc_s(a,b,c,d)-calc_w(a,b,c,d);
}
void Main() {
	n=rd(),m=rd();
	ans=calc_w(1,1,n,m);//while
	// printf("deb1:%lld\n",calc_w(1,1,n,m));
	int a=rd(),b=rd(),c=rd(),d=rd();
	int e=rd(),f=rd(),g=rd(),h=rd();
	ans+=calc_b(a,b,c,d);
	// printf("deb2:%lld\n",calc_b(a,b,c,d));
	ans-=calc_w(e,f,g,h);
	// printf("deb2:%lld\n",calc_w(e,f,g,h));
	ans-=calc_b(std::max(a,e),std::max(b,f),std::min(c,g),std::min(d,h));
	// printf("deb4:%lld\n",calc_b(std::max(a,e),std::max(b,f),std::min(c,g),std::min(d,h)));
	printf("%lld %lld\n",ans,calc_s(1,1,n,m)-ans);
}
signed main() {
	for(int T=rd();T;--T)Main();
}