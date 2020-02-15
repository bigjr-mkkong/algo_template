#include <bits/stdc++.h>
using namespace std;
const int maxn=1e3;
int val[maxn],key[maxn],size[maxn],ch[maxn][2],tot=0;
int root;
inline int rand()
{
	static int seed=19260817;
    return seed=(int)seed*482711LL%2147483647;
}
void pushup(int x){
	size[x]=size[ch[x][0]]+size[ch[x][1]]+1;
	return;
}
void split(int root,int& x,int& y,int value){
	if(!root){
		x=y=0;
		return;
	}
	if(val[root]<=value){
		x=root;
		split(ch[root][1],ch[x][1],y,value);
	}else{ 
		y=root;
		split(ch[root][0],x,ch[y][0],value);
	}
	pushup(root);
}
/*
void swap(int &a,int &b){
	int tmp=a;
	a=b;
	b=tmp;
}
void pushdown(int x){
	swap(ch[x][0],ch[x][1]);
	tag[x]^=1;
	tag[ch[x][0]]^=1;
	tag[ch[x][1]]^=1;
}
void split_k(int root, int k, int& x, int& y){
    if(!root){ x = y = 0; return; }
    if(tag[root]) pushdown(root);
    if(size[ch[root][0]]+1 <= k){
        x = root;
        split_k(ch[root][1], ch[root][1], y, k-size[ch[root][0]]-1);
    }
    else{

        y = root;
        split_k(ch[root][0], x, ch[root][0],k);
    }
    pushup(root);
}
void merge(int& root,int x,int y){
	if(!x||!y){
		root=x+y;
		return;
	}
	if(key[x]<key[y]){
		if(tag[x]) pushdown(x);
		root=x;
		merge(ch[root][1], ch[x][1],y);
	}else{
		if(tag[y]) pushdown(y);
		root=y;
		merge(ch[root][0],x,ch[y][0]);
	}
	pushup(root);
}
void rev(int x,int y){
	int l=0,r=0,t=0;
	split(root,x-1,l,t);
	split(t,y-x+1,t,r);
	tag[t]^=1;
	merge(l,l,t);
	merge(root,l,t);
}
*/
void merge(int& root,int x,int y){
	if(!x||!y){
		root=x+y;
		return;
	}
	if(key[x]<key[y]){
		root=x;
		merge(ch[root][1], ch[x][1],y);
	}else{
		root=y;
		merge(ch[root][0],x,ch[y][0]);
	}
	pushup(root);
}
void insert(int& root,int value){
	int x=0,y=0,z=++tot;
	val[z]=value,size[z]=1,key[z]=rand();
	split(root,x,y,value);
	merge(x,x,z);
	merge(root,x,y);
}
void del(int& root, int value){
	int x=0,y=0,z=0;
	split(root,x,y,value);
	split(x,x,z,value-1);
	merge(z,ch[z][0],ch[z][1]);
	merge(x,x,z);
	merge(root,x,y);

}
int kth_big(int root, int k){
	while(size[ch[root][0]]+1!=k){
		if(size[ch[root][0]]>=k){
			root=ch[root][0];
		}else{
			k-=size[ch[root][0]]+1;
			root=ch[root][1];
		}
	}
	return val[root];
}
int get_rank(int& root, int value){
	int x=0,y=0;
	split(root,x,y,value-1);
	int res=size[x]+1;
	merge(root,x,y);
	return res;
}
int get_pre(int& root, int value){
	int x=0,y=0;
	split(root,x,y,value-1);
	int res=kth_big(x,size[x]);
	merge(root,x,y);
	return res;
}
int get_suf(int& root, int value){
	int x=0,y=0;
	split(root,x,y,value);
	int res=kth_big(y,1);
	merge(root,x,y);
	return res;
} 
int seg_kth_big(int root, int l, int r, int k){
	int x=0,y=0,z=0,ans;
	split(root,x,y,val[l]-1);
	split(y,y,z,val[r]);
	ans=kth_big(y,k);
	merge(y,y,z);
	merge(root,x,y);
	return ans;
} 
int seg_get_rank(int root,int l,int r,int value){
	int x=0,y=0,z=0,ans;
	split(root,x,y,value-1);
	split(y,y,z,value);
	ans=get_rank(y,value);
	merge(y,y,z);
	merge(root,x,y);
	return ans;
} 
int main(void){
	memset(size,0,sizeof(size));
	  for(int i=1;i<=20;i++){
        insert(root,i);
	  }
	  printf("%d",get_suf(root,4));
}
