//---------------------------------结构体内重载----------------------
bool operator < (const edge &rhs) const {//小根堆 
        return value > rhs.value;
    }
bool operator > (const edge &rhs) const {//大根堆 
        return value < rhs.value;
    }
bool cmp(student a,student b){
    return a.achievement<b.achievement;
}
//---------------------------------gdc&lcm-------------------------
int gcd(int a, int b)
{
    int da = max(a,b);
    int xiao = min(a,b);
    if(da % xiao == 0)
        return xiao;
    else
	return gcd(xiao, da % xiao);

}
int lcm(int a, int b)
{
    return a*b / gcd(a, b);
}
//----------------------------------union find------------------------
int father[maxn+10];
void init() {
    for (int i = 1; i <= maxn+10; ++i) {
        father[i] = i;
    }
}
int get(int x) {
    if (father[x] == x) {
        return x;
    }
    return father[x] = get(father[x]);
}
void merge_f(int x, int y) {
    x = get(x);
    y = get(y);
    if (x != y) {
        father[y] = x;
    }
}
//----------------------------------fast power----------------------
#define ll long long
inline ll poww(ll a,int b,int mod){
    ll ans=1;
    while(b){
        if(b%2==1) ans=(ans*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    ans%=mod;
    return ans;
}
//-----------------------fast I/O-------------------------
inline void read(int &x){
    x = 0;
    char c = getchar();
    while(c<'0'||c>'9') c = getchar();
    while(c>='0'&&c<='9'){
        x = (x<<3)+(x<<1)+c-'0';
        c = getchar();
    }
}
//---------------------binary array---------------------------4
const int maxn=1e6+10;
int tree[maxn];
int lowbit(int n) 
{
    return n&(-n);
}
void add(int n,int now)
{
    while(n<=maxn)
    {
        tree[n]+=now;
        n+=lowbit(n);
    }
}
int sum(int n)
{
    int ans=0;
    while(n!=0)
    {
        ans+=tree[n];
        n-=lowbit(n);
    }
    return ans;
}
//----------------------01backpack-----------------------------
for(int i=1;i<=n;i++){
    for(int j=c;j>=w[i];j--){
            f[j]=max(f[j],f[j-w[i]]+v[i]);
    }
}
//----------------------entirely backpack-----------------------------
for(int i=1;i<=n;i++){
    for(int j=w[i];j<=c;j++){
            f[j]=max(f[j],f[j-w[i]]+v[i]);
    }
}
//--------------------------LIS--------------------------------
const int maxn=1e4;
int a[maxn],b[maxn];
int lis(int n){
	b[1]=a[1];
	int len=1;
	for(int i=2;i<=n;i++){
		if(a[i]>b[len]) b[++len]=a[i];
		else{
			int pos=lower_bound(b+1,b+1+len,a[i])-b;
			b[pos]=a[i];
		}
	}
	return len;
}
//-------------------------LCS------------------------------------
const int maxn=1e2;
int x[maxn],y[maxn];
int lcs(int a,int b){
	int dp[maxn][maxn]={0};
	for(int i=1;i<=a;i++){
		for(int j=1;j<=b;j++){
			if(x[i-1] == y[j-1]) dp[i][j]=max(dp[i][j],dp[i-1][j-1]+1);
			else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
		}
	}
	return dp[a][b];
}
//----------------------------bst-------------------------------
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAX=10000;
const int NIL=-1;//定义-1为空
int tree[MAX];

void insert(int root,int x)//插入操作
{
    if(tree[root]==NIL)
    {
        tree[root]=x;
        return ;
    }
    if(tree[root]>=x)
        insert(root*2,x);
    else
        insert(root*2+1,x);
}
bool search(int root,int x)
{
    while(tree[root]!=NIL)
    {
        if(tree[root]==x)
            return true;
        if(tree[root]>x)
            root*=2;
        else
            root=root*2+1;
    }
    return false;
}
void midser(int root)//中序遍历
{
    if(tree[root]==NIL)
        return ;
    else
    {
        midser(root*2);
        printf("%-3d",tree[root]);
        midser(root*2+1);
    }
}

int minval(int root)//返回最小值
{
    if(tree[root*2]==NIL)
        return tree[root];
    return minval(root*2);
}
void delnode(int root,int x)
{
    if(tree[root]>x)
        delnode(root*2,x);
    else if(tree[root]<x)
        delnode(root*2+1,x);
    else if(tree[root*2]!=NIL&&tree[root*2+1]!=NIL)
    {
        int key=minval(root*2+1);
        tree[root]=key;
        delnode(root*2+1,key);
    }
    else if(tree[root*2]==NIL&&tree[root*2+1]==NIL)
    {
        tree[root]=-1;

    }
    else
    {
        if(tree[root*2]==NIL)
        {
            tree[root]=tree[root*2+1];
            delnode(root*2+1,tree[root*2+1]);
        }
        else
        {
            tree[root]=tree[root*2];
            delnode(root*2,tree[root*2]);
        }
    }
}
//---------------------------------splay-----------------------------------  
const int MAXN=1000000;  
int ch[MAXN][2],f[MAXN],size[MAXN],cnt[MAXN],key[MAXN];  
int sz,root;  
inline void clear(int x){  
    ch[x][0]=ch[x][1]=f[x]=size[x]=cnt[x]=key[x]=0;  
}  
inline bool get(int x){  
    return ch[f[x]][1]==x;  
}  
inline void update(int x){
    if (x){  
        size[x]=cnt[x];  
        if (ch[x][0]) size[x]+=size[ch[x][0]];  
        if (ch[x][1]) size[x]+=size[ch[x][1]];  
    }  
}  
inline void rotate(int x){  
    int old=f[x],oldf=f[old],whichx=get(x);  
    ch[old][whichx]=ch[x][whichx^1]; f[ch[old][whichx]]=old;  
    ch[x][whichx^1]=old; f[old]=x;  
    f[x]=oldf;  
    if (oldf)  
        ch[oldf][ch[oldf][1]==old]=x;  
    update(old); update(x);  
}  
inline void splay(int x){  
    for (int fa;fa=f[x];rotate(x))  
      if (f[fa])  
        rotate((get(x)==get(fa))?fa:x);  
    root=x;  
}  
inline void insert(int x){  
    if (root==0){sz++; ch[sz][0]=ch[sz][1]=f[sz]=0; root=sz; size[sz]=cnt[sz]=1; key[sz]=x; return;}  
    int now=root,fa=0;  
    while(1){  
        if (x==key[now]){  
            cnt[now]++; update(now); update(fa); splay(now); break;  
        }  
        fa=now;  
        now=ch[now][key[now]<x];  
        if (now==0){  
            sz++;  
            ch[sz][0]=ch[sz][1]=0;  
            f[sz]=fa;  
            size[sz]=cnt[sz]=1;  
            ch[fa][key[fa]<x]=sz;  
            key[sz]=x;  
            update(fa);  
            splay(sz);  
            break;  
        }  
    }  
}  
inline int find(int x){  //find the rank of x 
    int now=root,ans=0;  
    while(1){  
        if (x<key[now])  
          now=ch[now][0];  
        else{  
            ans+=(ch[now][0]?size[ch[now][0]]:0);  
            if (x==key[now]){  
                splay(now); return ans+1;  
            }  
            ans+=cnt[now];  
            now=ch[now][1];  
        }  
    }
	return ans;  
}  
inline int findx(int x){  // find the value which rank is x
    int now=root;  
    while(1){  
        if (ch[now][0]&&x<=size[ch[now][0]])  
          now=ch[now][0];  
        else{  
            int temp=(ch[now][0]?size[ch[now][0]]:0)+cnt[now];  
            if (x<=temp) return key[now];  
            x-=temp; now=ch[now][1];  
        }  
    }  
    return now;
}  
inline int pre(){  
    int now=ch[root][0];  
    while (ch[now][1]) now=ch[now][1];  
    return key[now];  
}  
inline int next(){  
    int now=ch[root][1];  
    while (ch[now][0]) now=ch[now][0];  
    return key[now];  
}  
inline void del(int x){  
    int whatever=find(x);  
    if (cnt[root]>1){cnt[root]--; update(root); return;}  
    if (!ch[root][0]&&!ch[root][1]) {clear(root); root=0; return;}  
    if (!ch[root][0]){  
        int oldroot=root; root=ch[root][1]; f[root]=0; clear(oldroot); return;  
    }  
    else if (!ch[root][1]){  
        int oldroot=root; root=ch[root][0]; f[root]=0; clear(oldroot); return;  
    }  
    int leftbig=pre(),oldroot=root;  
    splay(leftbig);  
    ch[root][1]=ch[oldroot][1];  
    f[ch[oldroot][1]]=root;  
    clear(oldroot);  
    update(root);   
}  
inline int prex(int x){//ask the precursor of x
	insert(x);printf("%d\n",key[pre()]);del(x);
}
inline int nextx(int x){// ask the succeed of x
	insert(x);printf("%d\n",key[next()]);del(x);
}
void splay_to(int x,int tar){
	for(int fa;(fa=f[x])!=tar;rotate(x))
		if(f[fa]!=tar)
			rotate(get(fa==get(x)?fa:x));
	if(!tar) root=x;
	return;
}
