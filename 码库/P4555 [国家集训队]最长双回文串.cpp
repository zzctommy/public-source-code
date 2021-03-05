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

const int N=100005;
int n,pre[N],suf[N],ans;
int len[N],tot,las,fail[N],tr[N][26];
char str[N];
inline int getfail(int x,int i){
	while(i-len[x]-1<0||str[i-len[x]-1]!=str[i])x=fail[x];
	return x;
}
signed main(){
	scanf("%s",str),n=strlen(str);
	len[0]=0,fail[0]=1,len[1]=-1,fail[1]=0,tot=1,las=0;
	for(int i=0;i<n;++i){
		int c=str[i]-'a',f=getfail(las,i);
		if(!tr[f][c]){
			fail[++tot]=tr[getfail(fail[f],i)][c];
			len[tot]=len[f]+2;
			tr[f][c]=tot;
		}
		las=tr[f][c],pre[i]=len[las];
	}
	
	memset(tr,0,sizeof(tr)),memset(fail,0,sizeof(fail));
	memset(len,0,sizeof(len)),reverse(str,str+n);
	
	len[0]=0,fail[0]=1,len[1]=-1,fail[1]=0,tot=1,las=0;
	for(int i=0;i<n;++i){
		int c=str[i]-'a',f=getfail(las,i);
		if(!tr[f][c]){
			fail[++tot]=tr[getfail(fail[f],i)][c];
			len[tot]=len[f]+2;
			tr[f][c]=tot;
		}
		las=tr[f][c],suf[n-i-1]=len[las];
	}
	
	for(int i=0;i<n-1;++i)ckmax(ans,pre[i]+suf[i+1]);
	cout<<ans<<'\n';
}