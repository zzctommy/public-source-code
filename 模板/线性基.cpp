void insert(int x) {
	for(int i=A;~i;--i)
		if(x>>i&1) {
			if(d[i])x^=d[i];
			else return d[i]=x,void();
		}
}