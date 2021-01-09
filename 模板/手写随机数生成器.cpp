struct Rand{
	unsigned long long sa,sb,sc;
	static const int basic=(1<<30)-1;
	Rand(){
		srand(time(0));
		sa=1ull*::rand()*::rand();
		for(int i=1,up=::rand()%100;i<=up;++i)::rand();
		srand(::rand()^clock());
		sb=1ull*::rand()*::rand();
		for(int i=1,up=::rand()%100;i<=up;++i)::rand();
		srand(::rand()^clock());
		sc=1ull*::rand()*::rand();
	}
	void init(){
		srand(time(0));
		sa=1ull*::rand()*::rand();
		for(int i=1,up=::rand()%100;i<=up;++i)::rand();
		srand(::rand()^clock());
		sb=1ull*::rand()*::rand();
		for(int i=1,up=::rand()%100;i<=up;++i)::rand();
		srand(::rand()^clock());
		sc=1ull*::rand()*::rand();
	}
	inline int rand(){
		sa^=sa<<32,sa^=sa>>13,sa^=sa<<1;
		unsigned long long t=sa;
		sa=sb,sb=sc,sc^=t^sa;
		return static_cast<int>(sc&basic)+1;
	}
	int rad(int l,int r){return rand()%(r-l+1)+l;}
};