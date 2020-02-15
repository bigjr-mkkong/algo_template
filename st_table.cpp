#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int m[maxn][50],n,d;
int query(int l,int r){
	int k=log2(r-l+1);
	return max(m[l][k],m[r-(1<<k)+1][k]);
}
int main(void){
	scanf("%d %d",&n,&d);
	for(int i=1;i<=n;i++){
		scanf("%d",&m[i][0]);
	}
	for(int j=1;j<=21;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			m[i][j]=max(m[i][j-1],m[i+(1<<(j-1))][j-1]);
		}
	}
	for(int i=1;i<=d;i++){
		int l,r;
		scanf("%d %d",&l,&r);
		printf("%d\n",query(l,r));
	}
} 
