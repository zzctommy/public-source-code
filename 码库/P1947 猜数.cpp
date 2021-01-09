#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
extern "C" int Seniorious(int); 
extern "C" int Chtholly(int n, int c) {
	int l=1,r=n;
	while(l<=r) {
		int mid=(l+r)>>1,k=Seniorious(mid);
		if(!k)return mid;
		if(k<0)l=mid+1;
		else if(k>0)r=mid-1;
	}
}