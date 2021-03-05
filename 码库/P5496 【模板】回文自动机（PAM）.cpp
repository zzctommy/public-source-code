#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
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
const int N=500005;
int n,tot,las;
int len[N],num[N],fail[N],tr[N][26];
char str[N];
int getfail(int x,int i){
	while(i-len[x]-1<0||str[i]!=str[i-len[x]-1])x=fail[x];
	return x;
}
signed main(){
	scanf("%s",str),n=strlen(str);
	len[0]=0,num[0]=0,fail[0]=1;
	len[1]=-1,num[1]=0,fail[1]=0;
	las=0,tot=1;
	for(int i=0,lastans=0;i<n;++i){
		if(i>=1)str[i]=(str[i]-97+lastans)%26+97;
		int c=str[i]-'a',f=getfail(las,i);
		if(!tr[f][c]){
			fail[++tot]=tr[getfail(fail[f],i)][c];
			tr[f][c]=tot;
			len[tot]=len[f]+2;
			num[tot]=num[fail[tot]]+1;
		}
		las=tr[f][c];
		printf("%d ",lastans=num[las]);
	}
	return 0;
}