#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=100009;
int n,mx,st,ed;
vector<int>v[N];
signed main() {
    n=rd(),st=1,ed=0;
    for(int i=1;i<=n;++i) {
        int x=rd();
        if(mx>x)return printf("%d\n",i-1),0;
        if(st>ed){v[++ed].push_back(x);continue;}
        int l=st,r=ed,res=ed+1;
        while(l<=r) {
            int mid=(l+r)>>1;
            if(v[mid].front()>x)res=mid,r=mid-1;
            else l=mid+1;
        }
        while(!v[res].empty()&&v[res].back()<x)
            mx=max(mx,v[res].back()),v[res].pop_back();
        v[res].push_back(x),ed=max(ed,res);
    }
    printf("%d\n",n);return 0;
}