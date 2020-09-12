    #include<bits/stdc++.h>
    using namespace std;
    #define rint register int
    typedef long long LL;
    //#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
    //char buf[1<<21],*p1=buf,*p2=buf;
    inline int rd(){
       int x=0,f=1;
       char ch=getchar();
       while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
       while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
       return x*f;
    }
    const int N=200010;
    int T,n,a[N],bin[N],ans;
    signed main() {
    	T=rd();
    	while(T--) {
    		n=rd(),ans=0;
    		for(rint i=1;i<=n;++i)a[i]=rd(),++bin[a[i]];
    		int tmp=0;
    		for(rint i=1;i<=n;++i) {
    			ans+=(bin[i]+tmp)/i;
    			tmp=(bin[i]+tmp)%i;
    		}
    		for(rint i=1;i<=n;++i)bin[i]=0;
    		printf("%d\n",ans);
    	}
    	return 0;
    }