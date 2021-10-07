#include <bits/stdc++.h>
#define INF 2147483647 
using namespace std;
const int maxn=1e5+10,maxm=1e7;
int arr[maxn],n,m;
inline void read(int &x){
    x = 0;
    char c = getchar();
    while(c<'0'||c>'9') c = getchar();
    while(c>='0'&&c<='9'){
        x = (x<<3)+(x<<1)+c-'0';
        c = getchar();
    }
}
int val[maxm],size[maxm],l[maxm],r[maxm],key[maxm],tot=0;
struct fhq_treap {
	int root;

	void update(int x) {
		size[x]=size[l[x]]+size[r[x]]+1;
	}

	int merge(int x,int y) {
		if(!x||!y) return x+y;
		if(key[x]<key[y]) {
			return r[x]=merge(r[x],y),update(x),x;
		}
		return l[y]=merge(x,l[y]),update(y),y;
	}

	void split(int x,int value,int &u,int &v) {
		if(!x) {
			u=v=0;
			return;
		}
		if (val[x] <= value)
			u = x, split(r[x], value, r[u], v);
		else
			v = x, split(l[x], value, u, l[v]);
		update(x);
		return;
	}

	int create(int value) {
		val[++tot]=value;
		key[tot]=rand();
		size[tot]=1;
		return tot;
	}

	int x, y, z;

	void insert(int value) {
		split(root,value,x,y);
		root = merge(x,merge(create(value),y));
		return;
	}

	void build(int l,int r) {
		for(int i=l; i<=r; i++) insert(arr[i]);
	}

	void Delete(int value) {
		split(root,value,x,z);
		split(x,value-1,x,y);
		y=merge(l[y],r[y]);
		root=merge(x,merge(y,z));
	}

	int rank(int value) {
		split(root,value-1,x,y);
		int ans=size[x]+1;
		root=merge(x,y);
		return ans;
	}

	int findkey(int x, int rak) {
		if (rak<=size[l[x]])
			return findkey(l[x],rak);
		if (rak==size[l[x]]+1)
			return val[x];
		return findkey(r[x],rak-size[l[x]]-1);
	}

	int lower(int key) {
		split(root,key-1,x,y);
		int ans;
		if (size[x]) ans=findkey(x,size[x]);
		else ans=-INF;
		root=merge(x,y);
		return ans;
	}

	int upper(int key) {
		split(root,key,x,y);
		int ans;
		if (size[y]) ans=findkey(y,1);
		else ans=INF;
		root=merge(x,y);
		return ans;
	}
} ft[maxn<<2];

struct seg_tree {
	void build(int l,int r,int pos) {
		ft[pos].build(l,r);
		if(l!=r) {
			int mid=(l+r)>>1;
			build(l,mid,pos<<1);
			build(mid+1,r,pos<<1|1);
		}
		return;
	}

	int query_rank(int ll,int rr,int l,int r,int val,int pos){
		if(ll>r||rr<l) return 0;
		if(ll<=l&&rr>=r) return ft[pos].rank(val)-1;
		int mid=(l+r)/2;
		return query_rank(ll,rr,l,mid,val,pos<<1)+query_rank(ll,rr,mid+1,r,val,pos<<1|1);
	}

	int query_num(int l,int r,int rak){
		int x=0,y=INF,ans=-1;
		while(x<=y){
			int mid=(x+y)/2;
			if(query_rank(l,r,1,n,mid,1)+1<=rak){
				ans=mid;
				x=mid+1;
			}else{
				y=mid-1;
			}
		}
		return ans;
	}
	
	void update(int l,int r,int pos,int p,int val){
		ft[pos].Delete(arr[p]);
		ft[pos].insert(val);
		int mid=(l+r)/2;
		if(l!=r){
			if(p<=mid){
				update(l,mid,pos<<1,p,val);
			}else{
				update(mid+1,r,pos<<1|1,p,val);
			}
		}
	}
	
	int lower(int ll,int rr,int l,int r,int pos,int val){
		if(ll>r||rr<l) return -INF;
		if(ll<=l&&rr>=r) return ft[pos].lower(val);
		int mid=(l+r)/2;
		return max(lower(ll,rr,l,mid,pos<<1,val),lower(ll,rr,mid+1,r,pos<<1|1,val));
	}
	
	int upper(int ll,int rr,int l,int r,int pos,int val){
		if(ll>r||rr<l) return INF;
		if(ll<=l&&rr>=r) return ft[pos].upper(val);
		int mid=(l+r)/2;
		return min(upper(ll,rr,l,mid,pos<<1,val),upper(ll,rr,mid+1,r,pos<<1|1,val));
	}
	
} st;

int main(void) {
	read(n);read(m);
	for(int i=1; i<=n; i++) {
		read(arr[i]);
	}
	st.build(1,n,1);
	while(m--){
		int opt,l,r,k,pos;
		read(opt);
		if(opt==1){
			read(l);read(r);read(k);
			printf("%d\n",st.query_rank(l,r,1,n,k,1)+1);
		}else if(opt==2){
			read(l);read(r);read(k);
			printf("%d\n",st.query_num(l,r,k));
		}else if(opt==3){
			read(pos);read(k);
			st.update(1,n,1,pos,k);
			arr[pos]=k;
		}else if(opt==4){
			read(l);read(r);read(k);
			printf("%d\n",st.lower(l,r,1,n,1,k));
		}else{
			read(l);read(r);read(k);
			printf("%d\n",st.upper(l,r,1,n,1,k));
		}
	}
}
