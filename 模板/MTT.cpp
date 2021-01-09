namespace poly{
const db pi=acos(-1.0);
int rev[M],lg,lim;
struct cp{
	db x,y;
	cp(){x=y=0;}
	cp(db x_,db y_){x=x_,y=y_;}
	cp operator + (const cp&t)const{return cp(x+t.x,y+t.y);}
	cp operator - (const cp&t)const{return cp(x-t.x,y-t.y);}
	cp operator * (const cp&t)const{return cp(x*t.x-y*t.y,x*t.y+y*t.x);}
}w[M];
void init_poly(const int&n){
	for(lim=1,lg=0;lim<=n;lim<<=1,++lg);
	for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1)),w[i]=cp(cos(2.*pi*i/lim),sin(2.*pi*i/lim));
}
void FFT(cp*a,int op){
    for(int i=0;i<lim;++i)if(i>rev[i])swap(a[i],a[rev[i]]);
    for(int i=1,t=lim>>1;i<lim;i<<=1,t>>=1){
	    for(int j=0;j<lim;j+=i<<1){
		    for(int k=0;k<i;++k){
			    const cp X=a[j+k],Y=w[t*k]*a[i+j+k];
			    a[j+k]=X+Y,a[i+j+k]=X-Y;
			}
		}
	}
    if(!op)for(int i=0;i<lim;++i)a[i].x/=lim;
}
void MTT(int*f,int*g,int*ans){	
	static cp A[M],B[M],C[M],D[M],E[M],F[M],G[M];
	for(int i=0;i<lim;++i)
		A[i]=cp(f[i]&65535,0),B[i]=cp(f[i]>>16,0),
		C[i]=cp(g[i]&65535,0),D[i]=cp(g[i]>>16,0);
	FFT(A,1),FFT(B,1),FFT(C,1),FFT(D,1);
	for(int i=0;i<lim;++i)
		E[i]=A[i]*C[i],F[i]=A[i]*D[i]+B[i]*C[i],G[i]=B[i]*D[i],w[i].y*=-1;
	FFT(E,0),FFT(F,0),FFT(G,0);
	for(int i=0;i<lim;++i)
		ans[i]=LL(G[i].x+0.5)%mod,
		ans[i]=((65536ll*ans[i]%mod)+LL(F[i].x+0.5)%mod)%mod,
		ans[i]=((65536ll*ans[i]%mod)+LL(E[i].x+0.5)%mod)%mod,
		w[i].y*=-1;
}
}