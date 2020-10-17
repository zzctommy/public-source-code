#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=1005;
int n,num,lca,ind[N];
vector<int>leaf,e[N];
signed main(){
    scanf("%d",&n);
    for(int i=1;i<n;++i){
        int x,y;scanf("%d%d",&x,&y);
        ++ind[x],++ind[y],e[x].pb(y),e[y].pb(x);
    }
    for(int i=1;i<=n;++i)if(ind[i]==1)leaf.pb(i),++num;
    while(num>1){
        int x=leaf[num-1],y=leaf[num-2];
        printf("? %d %d\n",x,y),fflush(stdout);
        scanf("%d",&lca);
        if(lca==x||lca==y)return printf("! %d\n",lca),fflush(stdout),0;
        num-=2,leaf.pop_back(),leaf.pop_back();
        for(int i:e[x])if(--ind[i]==1)leaf.pb(i),++num;
        for(int i:e[y])if(--ind[i]==1)leaf.pb(i),++num;
        // for(int i:leaf)std::cerr<<i<<' ';std::cerr<<'\n';
    }
    printf("! %d\n",leaf[0]),fflush(stdout);
}