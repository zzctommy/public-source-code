#include<bits/stdc++.h>
using namespace std;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
typedef long long LL;
const int N=500009;
char s[N],t[N];
int n,m,p[N],num[2];
signed main() {
    scanf("%s%s",s+1,t+1);
    n=strlen(s+1),m=strlen(t+1);
    if(n<m)return printf("%s\n",s+1),0;
    p[1]=0;
    for(int i=2,j=0;i<=m;++i) {
        while(j&&t[j+1]!=t[i])j=p[j];
        if(t[j+1]==t[i])++j;
        p[i]=j;
    }
    for(int i=1;i<=n;++i)++num[s[i]-'0'];
    for(int i=1;i<=m;++i)
        if(num[t[i]-'0'])putchar(t[i]),--num[t[i]-'0'];
        else {
            while(num[0])putchar('0'),--num[0];
            while(num[1])putchar('1'),--num[1];
            return 0;
        }
    for(int i=1,flg=0;i<=n-m;++i) {
        for(int j=p[m]+1;j<=m;++j)
            if(num[t[j]-'0'])putchar(t[j]),--num[t[j]-'0'];
            else {flg=1;break;}
        if(flg){
            while(num[0])putchar('0'),--num[0];
            while(num[1])putchar('1'),--num[1];
            return 0;
        }
    }
}