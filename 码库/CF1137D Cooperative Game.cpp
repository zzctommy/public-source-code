#include<bits/stdc++.h>
using namespace std;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=1009;
int n;
char s[12];
signed main() {
    while("fyyAKIOI") {
        printf("next 0\n");
        fflush(stdout);
        scanf("%d",&n);
        for(int i=1;i<=n;++i)scanf("%s",s);
        printf("next 0 1\n");
        fflush(stdout);
        scanf("%d",&n);
        for(int i=1;i<=n;++i)scanf("%s",s);
        if(n==2)break;
    }
    while("fyyAKIOI") {
        printf("next 0 1 2 3 4 5 6 7 8 9\n");
        fflush(stdout);
        scanf("%d",&n);
        for(int i=1;i<=n;++i)scanf("%s",s);
        if(n==1)break;
    }
    printf("done\n");
    fflush(stdout);
}