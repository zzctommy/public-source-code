//Orz cyn2006
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
int n,k,tot,ch[N][26],fa[N];
char str[N];
bool can[2][N];
void insert(char*str){
	int len=strlen(str),u=0,dep=0;
	rep(i,0,len-1){
		int c=str[i]-'a';
		if(!ch[u][c])ch[u][c]=++tot,fa[tot]=u;
		u=ch[u][c],++dep;
	}
	can[0][u]=1,can[1][u]=0;//can[0][i]:存在必败策略；can[1][i]：存在必胜策略 
}
signed main(){
	n=read(),k=read();
	rep(i,1,n){
		static char str[N];
		scanf("%s",str),insert(str);
	}
	per(i,tot,1)can[0][fa[i]]|=!can[0][i],can[1][fa[i]]|=!can[1][i];
	if(can[0][0]&&can[1][0])puts("First");
	else if(!can[0][0]&&can[1][0])puts(k&1?"First":"Second");
	else puts("Second");
}