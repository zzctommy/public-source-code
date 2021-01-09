const int mod=998244353;
int qpow(int n,int k){
	int res=1;
	for(;k;k>>=1,n=1ll*n*n%mod)
		if(k&1)res=1ll*n*res%mod;
	return res;
}
struct mint{
	int x;
	void fmod(int&x){x+=x>>31&mod,x-=mod,x+=x>>31&mod;}
	mint(LL v=0){x=v%mod,x<0?x+=mod:0;}
	mint& operator += (const mint&t){fmod(x=x+t.x);return *this;}
	mint& operator -= (const mint&t){fmod(x=x-t.x);return *this;}
	mint& operator *= (const mint&t){x=1ll*x*t.x%mod;return *this;}
	mint& operator /= (const mint&t){x=1ll*x*qpow(t.x,mod-2)%mod;return *this;}
	friend mint operator + (const mint&a,const mint&b){return mint(a)+=b;}
	friend mint operator - (const mint&a,const mint&b){return mint(a)-=b;}
	friend mint operator * (const mint&a,const mint&b){return mint(a)*=b;}
	friend mint operator / (const mint&a,const mint&b){return mint(a)/=b;}
	mint operator -(){return !x?0:mod-x;}
	mint operator == (const mint&t){return x==t.x;}
	mint operator != (const mint&t){return x!=t.x;}
	mint operator < (const mint&t){return x<t.x;}
	mint operator > (const mint&t){return x>t.x;}
	mint operator <= (const mint&t){return x<=t.x;}
	mint operator >= (const mint&t){return x>=t.x;}
	friend ostream& operator << (ostream&stream,const mint&v){return stream<<v.x;}
	friend istream& operator >> (istream&stream,mint&v){return stream>>v.x;}
	explicit operator int() const{return x;}
};