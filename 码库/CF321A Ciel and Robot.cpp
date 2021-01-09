#include<bits/stdc++.h>
int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=105;
const int inf=1e9+6;
int n,X,Y,dx,dy,sx,sy;
char s[N];
signed main(){
    X=read(),Y=read();
    scanf("%s",s+1),n=strlen(s+1);
    for(int i=1;i<=n;++i){
        if(s[i]=='U')++dy;
        else if(s[i]=='D')--dy;
        else if(s[i]=='L')--dx;
        else ++dx;
    }
	if(sx==X&&sy==Y)return puts("Yes"),0;
	if(sx==X&&!dx){if(dy&&(Y-sy)%dy==0&&(Y-sy)/dy>=0)return puts("Yes"),0;}
	if(sy==Y&&!dy){if(dx&&(X-sx)%dx==0&&(X-sx)/dx>=0)return puts("Yes"),0;}
	if(dx&&dy){if((Y-sy)%dy==0&&(X-sx)%dx==0&&(Y-sy)/dy==(X-sx)/dx&&(X-sx)/dx>=0)return puts("Yes"),0;}
    for(int i=1;i<=n;++i){
        if(s[i]=='U')++sy;
        else if(s[i]=='D')--sy;
        else if(s[i]=='L')--sx;
        else ++sx;
		std::cerr<<sx<<' '<<sy<<'\n';
		if(sx==X&&sy==Y)return puts("Yes"),0;
		if(sx==X&&!dx){if(dy&&(Y-sy)%dy==0&&(Y-sy)/dy>=0)return puts("Yes"),0;}
		if(sy==Y&&!dy){if(dx&&(X-sx)%dx==0&&(X-sx)/dx>=0)return puts("Yes"),0;}
		if(dx&&dy){if((Y-sy)%dy==0&&(X-sx)%dx==0&&(Y-sy)/dy==(X-sx)/dx&&(X-sx)/dx>=0)return puts("Yes"),0;}
    }
    puts("No");
}//