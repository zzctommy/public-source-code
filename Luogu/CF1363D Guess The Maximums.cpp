#include <bits/stdc++.h>

int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
#define N 1009
int n,k,Max,book[N];
char s[10];
std::vector<int>v[N],ans;
void ask(int l,int r) {
	printf("? %d",r-l+1);
	for(int i=l;i<=r;++i)printf(" %d",i);
	puts("");
	fflush(stdout);
}
void ask(std::vector<int>v) {
	printf("? %d",(int)v.size());
	for(int i:v)printf(" %d",i);
	puts("");
	fflush(stdout);
}
void Main() {
	n=rd(),k=rd();
	for(int i=1;i<=k;++i) {
		int m=rd();
		for(int j=1;j<=m;++j)v[i].push_back(rd());
	}
	ask(1,n);
	Max=rd();
	int l=1,r=n,res=1;
	while(l<=r) {
		int mid=(l+r)>>1,k;
		ask(l,mid),k=rd();
		if(k<Max)l=mid+1;
		else res=mid,r=mid-1;
	}
	for(int i=1;i<=k;++i) {
		int flg=0;
		for(int j:v[i])if(j==res) {
			std::vector<int>tmp;
			for(int l:v[i])book[l]=1;
			for(int l=1;l<=n;++l)if(!book[l])tmp.push_back(l);
			flg=1;ask(tmp);ans.push_back(rd());
			for(int l:v[i])book[l]=0;
		}
		if(!flg)ans.push_back(Max);
	}
	printf("!");
	for(int i:ans)printf(" %d",i);
	puts("");
	fflush(stdout);
	scanf("%s",s);
	for(int i=1;i<=k;++i)v[i].clear();
	ans.clear();
}
signed main() {
	for(int T=rd();T;--T)Main();
}