    #include<bits/stdc++.h>
    using namespace std;
    #define rint register int
    typedef long long LL;
    #define int long long
    //#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
    //char buf[1<<21],*p1=buf,*p2=buf;
    inline int rd(){
       int x=0,f=1;
       char ch=getchar();
       while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
       while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
       return x*f;
    }
    int T,n,a;
    int mm(int x) {
    	if(!x)return 0;
    	int res=9;
    	while(x)  {
    		res=min(res,x%10);
    		x/=10;
    	}
    	return res;
    }
    int mx(int x) {
    	if(!x)return 0;
    	int res=0;
    	while(x) {
    		res=max(res,x%10);
    		x/=10;
    	}
    	return res;
    }
    signed main() {
    	T=rd();
    	while(T--) {
    		a=rd(),n=rd();
    		for(rint i=1;i<n;++i) {
    			if(!mm(a))break;
    			int tmp=mm(a)*mx(a);
    			a+=tmp;
    		}
    		printf("%lld\n",a);
    	}
    	return 0;
    } 
