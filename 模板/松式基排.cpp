void Sort(unsigned int*a,int n){
	static unsigned int _b[N];
	static unsigned int*b=_b;
	static int cnt[256];
	for(int i=0;i<32;i+=8){
		memset(cnt,0,sizeof(cnt));
		for(int j=n-1;j>=0;--j)++cnt[(a[j]>>i)&255];
		for(int j=0;j<256;++j)cnt[j]+=cnt[j-1];
		for(int j=n-1;j>=0;--j)b[--cnt[(a[j]>>i)&255]]=a[j];
		swap(a,b);
	}
}