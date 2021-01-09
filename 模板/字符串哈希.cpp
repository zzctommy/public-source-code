//调用手写随机数

template<int N>
struct String_Hash{

static const int O=N+5;
LL H1[O],H2[O],pw1[O],pw2[O],mod1,mod2;
int base1,base2;

String_Hash(){
	static const int base[8]={31,37,41,43,47,53,59,61};
	static const LL mod[8]={100000000000031ll,100000000000367ll,100000000000169ll,100000000000261ll,
	10000000000000069ll,10000000000000639ll,10000000000000753ll,10000000000000669ll};
	static Rand maker;
	base1=base[maker.rand()&7];
	while((base2=base[maker.rand()&7])==base1);
	mod1=mod[maker.rand()&7];
	while((mod2=mod[maker.rand()&7])==mod1);
	pw1[0]=1;for(int i=1;i<=N;++i)pw1[i]=pw1[i-1]*base1%mod1;
	pw2[0]=1;for(int i=1;i<=N;++i)pw2[i]=pw2[i-1]*base2%mod2;
}
void insert(char*str){
	int n=strlen(str);
	H1[0]=H2[0]=0;
	for(int i=0;i<n;++i)H1[i+1]=(H1[i]*base1+str[i]-'a'+1)%mod1;
	for(int i=0;i<n;++i)H2[i+1]=(H2[i]*base2+str[i]-'a'+1)%mod2;
}
LL mul(LL x,LL y,LL mod){
	LL res=x*y-(LL)((long double)x/mod*y+0.5)*mod;
	return res<0?res+mod:res;
}
pair<LL,LL>Hash_val(int l,int r){
	LL v1=(H1[r]-mul(H1[l-1],pw1[r-l+1],mod1)+mod1)%mod1;
	LL v2=(H2[r]-mul(H2[l-1],pw2[r-l+1],mod2)+mod2)%mod2;
	return mkp(v1,v2);
}

};