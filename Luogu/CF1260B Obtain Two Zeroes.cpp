#include<bits/stdc++.h>
using namespace std;
int n,a,b;
int main() {
	scanf("%d",&n);
	while(n--) {
		scanf("%d%d",&a,&b);
		if(a>b)swap(a,b);
		if(b>2*a){puts("NO");continue;}
		if((2*a-b)%3==0)puts("YES");
		else puts("NO");
	}
	return 0;
} 