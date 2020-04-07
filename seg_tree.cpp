#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=200010;
struct node{
	ll sum,tag;
}t[maxn<<2];
ll arr[maxn];
void update(ll pos){
	t[pos].sum=t[pos<<1].sum+t[pos<<1|1].sum;
}
void build(ll l,ll r,ll pos){
	if(l==r){
		t[pos].sum=arr[l];
		return;
	}
	ll mid=(l+r)/2;
	build(l,mid,pos<<1);
	build(mid+1,r,pos<<1|1);
	update(pos);
}
void f(ll pos,ll l,ll r,ll k)
{
    t[pos].tag=t[pos].tag+k;
    t[pos].sum=t[pos].sum+k*(r-l+1);
}
void pushdown(ll l,ll r,ll pos){
	if(!t[pos].tag) return;
	ll mid=(l+r)/2;
	f(pos<<1,l,mid,t[pos].tag);
	f(pos<<1|1,mid+1,r,t[pos].tag);
	t[pos].tag=0;
}
void add(ll tl,ll tr,ll l,ll r,ll v,ll pos){
	if(tl<=l&&tr>=r){
		t[pos].sum+=v*(r-l+1);
		t[pos].tag+=v;
		return;
	}
	if(r<tl||l>tr){
		return;
	}
	ll mid=(l+r)/2;
	pushdown(l,r,pos);
	add(tl,tr,l,mid,v,pos<<1);
	add(tl,tr,mid+1,r,v,pos<<1|1);
	update(pos);
}
ll query(ll tl,ll tr,ll l,ll r,ll pos){
	if(tl<=l&&tr>=r){
		return t[pos].sum;
	}
	if(tl>r||tr<l) return 0;
	ll mid=(l+r)/2,res=0;
	pushdown(l,r,pos);
	return query(tl,tr,l,mid,pos<<1)+query(tl,tr,mid+1,r,pos<<1|1);
}
int main(void){
	ios::sync_with_stdio(false);
	ll n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>arr[i];
	}
	build(1,n,1);
	for(int i=1;i<=m;i++){
		ll opt,x,y,k;
		cin>>opt;
		if(opt==1){
			cin>>x>>y>>k;
			add(x,y,1,n,k,1);
		}else{
			cin>>x>>y;
			cout<<query(x,y,1,n,1)<<endl;
		}
	}
}
