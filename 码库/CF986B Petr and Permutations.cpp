#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1000005],r[1000005];
long long ans;
inline int rd()
{
	int f=1,x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void msort(int left,int right)
{
	if(left==right)return;
	int mid=(left+right)/2;
	msort(left,mid);msort(mid+1,right);
	int i=left,j=mid+1,k=left;
	while(i<=mid&&j<=right)
	{
		if(a[i]>a[j])
		{
			ans+=mid-i+1;
			r[k++]=a[j++];
		}
		if(a[i]<=a[j])
		r[k++]=a[i++];
	}
	while(i<=mid)r[k++]=a[i++];
	while(j<=right)r[k++]=a[j++];
	for(int t=left;t<=right;t++)
		a[t]=r[t];
	return;
}
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	msort(1,n);
	if(ans%2==3*n%2)puts("Petr");
	else puts("Um_nik");
	return 0;
}