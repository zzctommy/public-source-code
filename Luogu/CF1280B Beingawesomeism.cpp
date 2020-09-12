    #include<bits/stdc++.h>
    using namespace std;
    #define rint register int
    //#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
    //char buf[1<<21],*p1=buf,*p2=buf;
    inline int rd() {
        int x=0,f=1;char ch=getchar();
        while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
        while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
        return x*f;
    }
    char rdc() {
    	char ch=getchar();
    	while(ch!='P'&&ch!='A')ch=getchar();
    	return ch=='A';
    }
    const int N=70;
    int T,r,c,a[N][N];
    bool pdn() {
    	int res=0;
    	for(rint i=1;i<=r;++i)
    		for(rint j=1;j<=c;++j)
    			res+=a[i][j];
    	return res==0;
    }
    bool pdy() {
    	int res=0;
    	for(rint i=1;i<=r;++i)
    		for(rint j=1;j<=c;++j)
    			res+=a[i][j];
    	return res==r*c;
    }
    bool pd1() {
    	int res;
    	res=0;for(rint i=1;i<=c;++i)res+=a[1][i];if(res==c)return 1;
    	res=0;for(rint i=1;i<=c;++i)res+=a[r][i];if(res==c)return 1;
    	res=0;for(rint i=1;i<=r;++i)res+=a[i][1];if(res==r)return 1;
    	res=0;for(rint i=1;i<=r;++i)res+=a[i][c];if(res==r)return 1;
    	return 0;
    }
    bool pd2() {
    	if(a[1][c]||a[r][c]||a[r][1]||a[1][1])return 1;
    	for(rint i=2;i<r;++i) {
    		int res=0;
    		for(rint j=1;j<=c;++j)res+=a[i][j];
    		if(res==c)return 1;
    	}
    	for(rint j=2;j<c;++j) {
    		int res=0;
    		for(rint i=1;i<=r;++i)res+=a[i][j];
    		if(res==r)return 1;
    	}
    	return 0;
    }
    bool pd3() {
    	int res=0;
    	for(rint i=2;i<c;++i)res+=a[1][i];
    	for(rint i=2;i<c;++i)res+=a[r][i];
    	for(rint i=2;i<r;++i)res+=a[i][1];
    	for(rint i=2;i<r;++i)res+=a[i][c];
    	return res>0;
    }
    signed main() {
    	T=rd();
    	while(T--) {
    		r=rd(),c=rd();
    		for(rint i=1;i<=r;++i)
    			for(rint j=1;j<=c;++j)	
    				a[i][j]=rdc();
    		if(pdy())puts("0");
    		else if(pdn())puts("MORTAL");
    		else if(pd1())puts("1");
    		else if(pd2())puts("2");
    		else if(pd3())puts("3");
    		else puts("4");
    	}
    	return 0;
    }
