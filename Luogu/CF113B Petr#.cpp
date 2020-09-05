#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
const int N=2005;
const int pr=131;
ull power[N],h[N],b,e;
char t[N],sb[N],se[N];
int tx,ty,x[N],y[N],lt,lb,le,ans;
void pre() {
	power[0]=1;
	for(int i=1; i<=lt; ++i)
		power[i]=power[i-1]*pr,h[i]=h[i-1]*pr+t[i]-'a'+1;
	for(int i=1; i<=lb; ++i)b=b*pr+sb[i]-'a'+1;
	for(int i=1; i<=le; ++i)e=e*pr+se[i]-'a'+1;
}
ull has(int l,int r) {
	return h[r]-h[l-1]*power[r-l+1];
}
unordered_map<ull,bool>mp;
int main() {
	scanf("%s%s%s",t+1,sb+1,se+1);
	lt=strlen(t+1);
	lb=strlen(sb+1);
	le=strlen(se+1);
	pre();
	for(int i=1; i<=lt-lb+1; ++i) 
		if(has(i,i+lb-1)==b)x[++tx]=i;
	for(int i=le; i<=lt; ++i)
		if(has(i-le+1,i)==e)y[++ty]=i;
	for(int i=1; i<=tx; ++i)
		for(int j=1; j<=ty; ++j)
			if(x[i]<=y[j]&&y[j]-x[i]+1>=max(le,lb))
			{
				ull ha=has(x[i],y[j]);
				if(!mp[ha])++ans,mp[ha]=true;
			}
	printf("%d\n",ans);
	return 0;
}