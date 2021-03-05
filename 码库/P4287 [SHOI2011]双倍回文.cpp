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
int n,ans;
int tot,las,len[N],trans[N],tr[N][26],fail[N];
char str[N];
inline int getfail(int x,int i){
	while(i-len[x]-1<0||str[i]!=str[i-len[x]-1])x=fail[x];
	return x;
}
inline int gettrans(int x,int i,int lim){
	while(2*(len[x]+2)>lim||str[i]!=str[i-len[x]-1])x=fail[x];
	return x;
}
void build(char*str,int n){
	len[0]=0,fail[0]=1,len[1]=-1,fail[1]=0,tot=1;
	for(int i=0;i<n;++i){
		int c=str[i]-'a',f=getfail(las,i);
		if(!tr[f][c]){
			fail[++tot]=tr[getfail(fail[f],i)][c];
			tr[f][c]=tot;
			len[tot]=len[f]+2;
			if(len[tot]<=2)trans[tot]=fail[tot];
			else trans[tot]=tr[gettrans(trans[f],i,len[tot])][c];
		}
		las=tr[f][c];
	}
}
signed main(){
	scanf("%d%s",&n,str);
	build(str,strlen(str));
	for(int i=1;i<=tot;++i)
		if(len[trans[i]]%2==0&&len[trans[i]]*2==len[i])ckmax(ans,len[i]);
	cout<<ans<<'\n';
	return 0;
}