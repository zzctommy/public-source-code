const int N=605;
int n,mod,a[N][N];
void fmod(int&x){x+=x>>31&mod,x-=mod,x+=x>>31&mod;}
int Gauss(){
	int res=1;
	rep(i,1,n){
		rep(j,i+1,n){
			while(a[j][i]){
				int div=a[i][i]/a[j][i];
				rep(k,i,n)fmod(a[i][k]-=1ll*div*a[j][k]%mod),swap(a[i][k],a[j][k]);
				res*=-1;
			}
		}
		if(!a[i][i])return 0;
		res=1ll*res*a[i][i]%mod;
	}
	return fmod(res),res;
}