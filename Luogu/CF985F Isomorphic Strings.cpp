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
void insert(char*str,int c){
    int n=strlen(str);
    H1[0]=H2[0]=0;
    for(int i=0;i<n;++i)if(str[i]-'a'==c)H1[i+1]=(H1[i]*base1+2)%mod1;else H1[i+1]=(H1[i]*base1+1)%mod1;
    for(int i=0;i<n;++i)if(str[i]-'a'==c)H2[i+1]=(H2[i]*base2+2)%mod2;else H2[i+1]=(H2[i]*base2+1)%mod2;
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
const int N=200005;
String_Hash<N>H[26];
int n,m,sum[N][26];
char str[N];
signed main(){
	scanf("%d%d%s",&n,&m,str+1);
    rep(i,1,25)H[i]=H[0];
    rep(i,0,25)H[i].insert(str+1,i);
	rep(i,1,n){
        rep(j,0,25)sum[i][j]=sum[i-1][j];
        ++sum[i][str[i]-'a'];
    }
    while(m--){
        static pair<int,int>X[26],Y[26];
        static int sx[26],sy[26];
        int x=read(),y=read(),len=read(),ans=1;
        rep(i,0,25)sx[i]=sum[x+len-1][i]-sum[x-1][i],sy[i]=sum[y+len-1][i]-sum[y-1][i];
        sort(sx,sx+26),sort(sy,sy+26);
        rep(i,0,25)if(sx[i]!=sy[i]){ans=0;break;}
        if(!ans){puts("NO");continue;}
        rep(i,0,25)X[i]=H[i].Hash_val(x,x+len-1),Y[i]=H[i].Hash_val(y,y+len-1);
        sort(X,X+26),sort(Y,Y+26);
        rep(i,0,25)if(X[i]!=Y[i]){ans=0;break;}
        puts(ans?"YES":"NO");
    }
    return 0;
}
/*
10 1
accbaaccac
6 8 3

7 4
abacaba
1 1 1
1 4 2
2 1 3
2 4 3

*/