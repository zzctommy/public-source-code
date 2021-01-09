LL mul(LL x,LL y,LL mod){
	LL res=x*y-(LL)((long double)x/mod*y+0.5)*mod;
	return res<0?res+mod:res;
}
LL qpow(LL n,LL k,LL mod){
	LL res=1;for(;k;k>>=1,n=mul(n,n,mod))if(k&1)res=mul(res,n,mod);return res;
}
LL gcd(LL x,LL y){
	while(y){LL t=x%y;x=y,y=t;}
	return x;
}
namespace MR{
static const int pri[10]={2,3,5,7,11,13,17,19,61,233};
bool mr(LL x,LL p){
	if(x%p==0||qpow(p,x-1,x)!=1)return 0;
	LL k=x-1;
	while(!(k&1)){
		LL t=qpow(p%x,k>>=1,x);
		if(t!=1&&t!=x-1)return 0;
		if(t==x-1)break;
	}
	return 1;
}
bool test(LL x){
	for(int i=0;i<10;++i){
		if(x==pri[i])return 1;
		if(!mr(x,pri[i]))return 0;
	}
	return 1;
}

}

namespace PR{
LL ans,d[150];
int tot;
mt19937_64 rnd(673);
#define rad(l,r) (rnd()%((r)-(l)+1)+l)
LL pr(LL x,LL c){
	if(x==4)return 2;
	LL v0=c,v1=mul(v0,v0,x)+c,g=1;tot=0;
	while(true){
		g=mul(g,v1-v0,x),d[++tot]=v1-v0;
		if(tot==127){if(gcd(g,x)>1)break;tot=0;}
		v0=mul(v0,v0,x)+c,v1=mul(v1,v1,x)+c,v1=mul(v1,v1,x)+c;
	}
	for(int i=1;i<=tot;++i){g=gcd(d[i],x);if(g>1)return g;}
	return x;
}
void solve(LL x){
	if(x<=ans)return;
	if(MR::test(x))return ckmax(ans,x),void();
	LL y=x;while(y==x)y=pr(x,rad(1,x-1));
	while(x%y==0)x/=y;solve(x),solve(y);
}

LL work(LL x){return ans=1,solve(x),ans;}

}