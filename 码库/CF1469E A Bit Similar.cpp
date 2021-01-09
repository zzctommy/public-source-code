#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
struct Rand{
	unsigned long long sa,sb,sc;
	static const int basic=(1<<30)-1;
	Rand(){
		srand(time(0));
		sa=1ull*::rand()*::rand();
		for(int i=1,up=::rand()%100;i<=up;++i)::rand();
		srand(::rand()^clock());
		sb=1ull*::rand()*::rand();
		for(int i=1,up=::rand()%100;i<=up;++i)::rand();
		srand(::rand()^clock());
		sc=1ull*::rand()*::rand();
	}
	void init(){
		srand(time(0));
		sa=1ull*::rand()*::rand();
		for(int i=1,up=::rand()%100;i<=up;++i)::rand();
		srand(::rand()^clock());
		sb=1ull*::rand()*::rand();
		for(int i=1,up=::rand()%100;i<=up;++i)::rand();
		srand(::rand()^clock());
		sc=1ull*::rand()*::rand();
	}
	inline int rand(){
		sa^=sa<<32,sa^=sa>>13,sa^=sa<<1;
		unsigned long long t=sa;
		sa=sb,sb=sc,sc^=t^sa;
		return static_cast<int>(sc&basic)+1;
	}
	int rad(int l,int r){return rand()%(r-l+1)+l;}
};

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
void insert(char*str,int n){
	H1[0]=H2[0]=0;
	for(int i=1;i<=n;++i)H1[i]=(H1[i-1]*base1+str[i]-'0'+1)%mod1;
	for(int i=1;i<=n;++i)H2[i]=(H2[i-1]*base2+str[i]-'0'+1)%mod2;
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
const int N=1000005;
String_Hash<N>hs;
int n,k,ans[N];
char S[N],T[N];
void Main(){
	scanf("%d%d%s",&n,&k,S+1);
	for(int i=1;i<=n;++i)T[i]='1'-S[i]+'0';
	map<pair<LL,LL>,bool>mp;
	hs.insert(T,n);
	for(int i=1;i<=n-k+1;++i)mp[hs.Hash_val(i,i+k-1)]=1;//,cerr<<hs.Hash_val(i,i+k-1).fi<<' '<<hs.Hash_val(i,i+k-1).se<<'\n';
	// rep(i,1,n)cerr<<hs.H1[i]<<' ';cerr<<'\n';
	// rep(i,1,n)cerr<<hs.H2[i]<<' ';cerr<<'\n';
	LL h1=0,h2=0;
	for(int i=1;i<=k;++i)h1=(h1*hs.base1+1)%hs.mod1;
	for(int i=1;i<=k;++i)h2=(h2*hs.base2+1)%hs.mod2;
	for(int i=0;i<=k;++i)ans[i]=0;
	for(int i=0;i<=n-k+1;++i){
		// for(int j=1;j<=k;++j)putchar(ans[j]+'0');cerr<<":"<<h1<<' '<<h2<<'\n';
		if(!mp[mkp(h1,h2)]){
			puts("YES");
			for(int j=1;j<=k;++j)putchar(ans[j]+'0');
			puts("");
			return;
		}
		++ans[k],h1=(h1+1)%hs.mod1,h2=(h2+1)%hs.mod2;
		int j=k;
		while(ans[j]>1){
			ans[j]=0,++ans[j-1];
			h1=(h1+hs.pw1[k-j+1]-2ll*hs.pw1[k-j]%hs.mod1+hs.mod1)%hs.mod1;
			h2=(h2+hs.pw2[k-j+1]-2ll*hs.pw2[k-j]%hs.mod2+hs.mod2)%hs.mod2;
			--j;
		}
		if(j<=0)break;
	}
	puts("NO");
}
signed main(){for(int T=read();T;--T)Main();}