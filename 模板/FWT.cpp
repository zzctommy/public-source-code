const int N=18;
const int mod=998244353;
int m,n,a[1<<N],b[1<<N],A[1<<N],B[1<<N];
void fmod(int&x){x+=x>>31&mod,x-=mod,x+=x>>31&mod;}
void OR(int*a,int op){
	for(int o=2,k=1;k<n;o<<=1,k<<=1)
		for(int i=0;i<n;i+=o)
			for(int j=0;j<k;++j)
				fmod(a[i+j+k]+=a[i+j]*op);
}
void AND(int*a,int op){
	for(int o=2,k=1;k<n;o<<=1,k<<=1)
		for(int i=0;i<n;i+=o)
			for(int j=0;j<k;++j)
				fmod(a[i+j]+=a[i+j+k]*op);
}
void XOR(int*a,int op){
	for(int o=2,k=1;k<n;o<<=1,k<<=1)
		for(int i=0;i<n;i+=o)
			for(int j=0;j<k;++j){
				int x=a[i+j],y=a[i+j+k];
				fmod(a[i+j]=x+y),fmod(a[i+j+k]=x-y),a[i+j]=1ll*a[i+j]*op%mod,a[i+j+k]=1ll*a[i+j+k]*op%mod;
			}
}