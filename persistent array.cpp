#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
struct node {
	int l,r,sum;
} t[maxn*40];
int n,m,arr[maxn],cnt,root[maxn];
void build(int l,int r,int &now) {
	now=++cnt;
	if(l==r) {
		t[now].sum=arr[l];
		return;
	}
	int mid=(l+r)/2;
	build(l,mid,t[now].l);
	build(mid+1,r,t[now].r);
}
void modify(int l,int r,int ver,int &now,int pos,int num){
	t[now=++cnt]=t[ver];
	if(l==r){
		t[now].sum=num;
		return;
	}
	int mid=(l+r)/2;
	if(pos<=mid) modify(l,mid,t[ver].l,t[now].l,pos,num);
	else modify(mid+1,r,t[ver].r,t[now].r,pos,num);
}
int query(int l,int r,int now,int pos){
	if(l==r) return t[now].sum;
	int mid=(l+r)/2;
	if(pos<=mid) return query(l,mid,t[now].l,pos);
	else return query(mid+1,r,t[now].r,pos);
}
int main(void) {
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++) {
		scanf("%d",&arr[i]);
	}
	build(1,n,root[0]);
	for(int i=1; i<=m; i++) {
		int ver,opt,loc,val;
		scanf("%d %d",&ver,&opt);
		if(opt==1) {
			scanf("%d %d",&loc,&val);
			modify(1,n,root[ver],root[i],loc,val);
		} else {
			scanf("%d",&loc);
			printf("%d\n",query(1,n,root[ver],loc));
			root[i]=root[ver];
		}
	}
}
