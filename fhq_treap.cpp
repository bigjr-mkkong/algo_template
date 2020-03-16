#include <bits/stdc++.h>
#define INF 0x3f3f3f
using namespace std;
const int maxn=1e5+10;
int arr[maxn],n,m;
int val[maxn],size[maxn],l[maxn],r[maxn],key[maxn],tot=0;
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
}ft;

int main(void){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int opt,x;
		scanf("%d %d",&opt,&x);
		if(opt==1){
			ft.insert(x);
		}else if(opt==2){
			ft.Delete(x);
		}else if(opt==3){
			printf("%d\n",ft.rank(x));
		}else if(opt==4){
			printf("%d\n",ft.findkey(ft.root,x));
		}else if(opt==5){
			printf("%d\n",ft.lower(x));
		}else{
			printf("%d\n",ft.upper(x));
		}
	}
}
