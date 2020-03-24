#include <bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
struct node{
	int sum,l,r;
}hjt[maxn*40];
int n,m,root[maxn],cnt=0,arr[maxn];
vector<int> v;
int getindex(int val){
	return lower_bound(v.begin(),v.end(),val)-v.begin()+1;
}
void insert(int l,int r,int pre,int &now,int p){
	hjt[++cnt]=hjt[pre];
	now=cnt;
	hjt[now].sum++;
	if(l==r){
		return;
	}
	int mid=(l+r)/2;
	if(p<=mid) insert(l,mid,hjt[pre].l,hjt[now].l,p);
	else insert(mid+1,r,hjt[pre].r,hjt[now].r,p);
}

int query(int l,int r,int L,int R,int k){
	if(l==r) return l;
	int mid=(l+r)/2;
	int tmp=hjt[hjt[R].l].sum-hjt[hjt[L].l].sum;
	if(k<=tmp) return query(l,mid,hjt[L].l,hjt[R].l,k);
	else return query(mid+1,r,hjt[L].r,hjt[R].r,k-tmp);
}
int main(void){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&arr[i]);
		v.push_back(arr[i]);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for(int i=1;i<=n;i++){
		insert(1,n,root[i-1],root[i],getindex(arr[i]));
	}
	while(m--){
		int l,r,k;
		scanf("%d %d %d",&l,&r,&k);
		printf("%d\n",v[query(1,n,root[l-1],root[r],k)-1]);
	} 
}
