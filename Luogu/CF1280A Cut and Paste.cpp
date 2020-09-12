    #include<bits/stdc++.h>
    using namespace std;
    typedef long long LL;
    #define rint register int
    //#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
    //char buf[1<<21],*p1=buf,*p2=buf;
    inline int rd() {
    	int x=0,f=1;char ch=getchar();
    	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    	return x*f;
    }
    const int N=1050;
    const int mod=1e9+7;
    int T,x,it,n;
    LL ans;
    string s;
    signed main() {
    	T=rd();
    	while(T--) {
    		x=rd(),it=0,cin>>s,ans=n=s.length();
    		for(rint i=0;i<x;++i) {
    			if(s.length()>=x)ans=(ans+1ll*(ans-i-1+mod)*(s[i]-'1')%mod)%mod;
    			else {
    				if(s[i]=='2')s+=s.substr(i+1);
    				else if(s[i]=='3')s+=s.substr(i+1)+s.substr(i+1);
    				ans=s.length();
    			}
    		}
    		printf("%lld\n",ans);
    	}
    	return 0;
    }