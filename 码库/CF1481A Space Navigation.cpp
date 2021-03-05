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
const int N=100005;
int n,px,py;
char str[N];
void Main(){
    px=read(),py=read();
    scanf("%s",str+1),n=strlen(str+1);
    int cx=0,cy=0;
    if(px<0){
        rep(i,1,n)if(str[i]=='L')++cx;
    }else{
        rep(i,1,n)if(str[i]=='R')++cx;
    }
    if(py<0){
        rep(i,1,n)if(str[i]=='D')++cy;
    }else{
        rep(i,1,n)if(str[i]=='U')++cy;
    }
    puts(cx>=abs(px)&&cy>=abs(py)?"YES":"NO");
}
signed main(){for(int T=read();T;--T)Main();}