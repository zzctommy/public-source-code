const int N=2010;
const int base=10000;
const int limit=4;
int power_10[6]={1,10,100,1000,1000,10000};
struct num {
	LL a[N],len;
	num(){memset(a,0,sizeof(a)),len=0;}
	void init(LL x) {
		while(x)a[len++]=x%base,x/=base;
	}
	void read() {
		char s[2010];
		scanf("%s",s);
		len=1;
		int n=strlen(s),t=0;
		for(rint i=n-1;~i;--i,++t) {
			a[len-1]+=(s[i]-'0')*power_10[t];
			if(t+1==limit)t=-1,++len;
		}
		if(!t)--len;
	}
	void print(char c=-1) {
		printf("%lld",a[len-1]);
		for(rint i=len-2;i>=0;--i)printf("%0*lld",limit,a[i]);
		if(~c)putchar(c);
	}
};
num operator + (const num &a,const num &b) {
	num c;int mx=max(a.len,b.len);c.len=mx;
	for(rint i=0;i<mx;++i)c.a[i]=a.a[i]+b.a[i];
	for(rint i=0;i<mx;++i)if(c.a[i]>=base)++c.a[i+1],c.a[i]-=base;
	if(c.a[c.len])++c.len;
	return c;
}
num operator - (const num &a,const num &b) {
	num c;int mx=a.len;c.len=mx;
	for(rint i=0;i<mx;++i)c.a[i]=a.a[i]-b.a[i];
	for(rint i=0;i<mx;++i)if(c.a[i]<0)--c.a[i+1],c.a[i]+=base;
	while(c.len&&!c.a[c.len-1])--c.len;
	return c;
}
num operator * (const num &a,const num &b) {
	num c;int mx=a.len+b.len-1;c.len=mx;
	for(rint i=0,mxa=a.len;i<mxa;++i)
		for(rint j=0,mxb=b.len;j<mxb;++j) {
			c.a[i+j]+=a.a[i]*b.a[j];
			if(c.a[i+j]>=base)c.a[i+j+1]+=c.a[i+j]/base,c.a[i+j]%=base;
		}
	if(c.a[c.len])++c.len;
	return c; 
}
num operator / (const num &a,const int &b) {
	num c;int mx=a.len;
	LL now=0;
	for(rint i=mx-1,s=0;~i;--i) {
		now=now*base+a.a[i];
		if(now/b)s=1;
		if(!s)continue;
		c.a[c.len++]=now/b;
		now%=b;
	}
	reverse(c.a,c.a+c.len);
	return c;
}
bool operator < (const num &a,const num &b) {
	if(a.len!=b.len)return a.len<b.len;
	for(rint i=a.len-1;~i;--i)if(a.a[i]!=b.a[i])return a.a[i]<b.a[i];
	return 0;
}