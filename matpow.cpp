#include <bits/stdc++.h>
using namespace std;
const int N=2;
const int M=19260817;
struct mat{
	long long int m[N][N];
};
mat A={1,1,1,0},I={1,0,0,1};
mat matmul(mat a,mat b,int mod){
mat c;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			c.m[i][j]=0;
			for(int k=0;k<N;k++)
				c.m[i][j]+=a.m[i][k]*b.m[k][j]%mod;
			c.m[i][j]%=mod;
		}
	}
	return c;
}
mat matpow(mat a,int k,int mod){
	mat ans=I,p=A;
	while(k)
	{
		if(k&1)
		{
			ans=matmul(ans,p,mod);
			k--;
		}
		k>>=1;
		p=matmul(p,p,mod);
	}
	return ans;
}
int main(void){
	int n;
	scanf("%d",&n);
	mat ans=matpow(A,n-1,M);
	printf("%lld",ans.m[0][0]);
}
