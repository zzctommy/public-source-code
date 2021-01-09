#include<bits/stdc++.h>
using namespace std;
#define rint register int
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
int T,n,m,ans;
bool flag;
const int N=100010;
char s[N],t[N];
vector<int>v[26];
int main() {
	T=rd();
	while(T--) {
		ans=flag=0;scanf("%s%s",s+1,t+1);
		n=strlen(s+1),m=strlen(t+1);
		for(rint i=0;i<26;++i)v[i].clear();
		for(rint i=1;i<=n;++i)v[s[i]-'a'].push_back(i);
		for(rint i=1,lst=0,tmp;i<=m;++i) {
			tmp=t[i]-'a';
			if(v[tmp].empty()) {flag=1;break;}
			if(v[tmp].back()<=lst)++ans,lst=v[tmp].front();
			else lst=v[tmp][upper_bound(v[tmp].begin(),v[tmp].end(),lst)-v[tmp].begin()];
		}
		if(flag)puts("-1");
		else printf("%d\n",ans+1);
	}
	return 0;
}