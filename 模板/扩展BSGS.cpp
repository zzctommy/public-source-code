#define int long long
int a,p,b,ans;
int BSGS(int k,int a,int p,int b) {
	map<int,int>mp;
	int m=ceil(sqrt(p)),t=1;
	for(int i=1;i<=m;++i)t=t*a%p,mp[t*b%p]=i;
	for(int i=1;i<=m;++i) {
		k=k*t%p;
		if(mp.find(k)!=mp.end()) {
			return ((i*m-mp[k])%p+p)%p;
		}
	}
	return -1;
}
int gcd(int x,int y) {return !y?x:gcd(y,x%y);}
int exBSGS(int a,int p,int b) {
	a%=p,b%=p;
	if(b==1||p==1)return 0;
	int cnt=0,d,k=1,res;
	while((d=gcd(a,p))!=1) {
		if(b%d)return -1;
		++cnt,b/=d,p/=d;
		k=a/d*k%p;
		if(k==b)return cnt;
	}
	res=BSGS(k,a,p,b);
	if(~res)return res+cnt;
	else return -1;
}