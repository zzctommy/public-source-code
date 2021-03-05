#include<bits/stdc++.h>
#define ll long long
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define _rep(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define db double
#define N 200005

int n,cnt[N];

signed main(){
	int T;std::cin>>T;
	while(T--){
		std::cin>>n;
		for(int i=0;i<n;++i)cnt[i]=0;;
		for(int i=0,x;i<n;++i){
			std::cin>>x,x+=i;
			++cnt[(x%n+n)%n];
		}
		bool flg=0;
		for(int i=0;i<n;++i)if(cnt[i]>1){flg=1;break;}
		if(flg)std::cout<<"NO\n";
		else std::cout<<"YES\n";
	}
	return 0;
}