#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
struct node{
    int child[26];
    int times;
}trie[maxn];
int n,m,t=0;
string x;
void insert(string s){
    int l=s.length(),pos=0;
    for(int i=0;i<l;i++){
        if(trie[pos].child[s[i]-'a']==0){
            trie[pos].child[s[i]-'a']=++t;
        }
        pos=trie[pos].child[s[i]-'a'];
    }
}

int find(string s){
    int l=s.length(),pos=0;
    for(int i=0;i<l;i++){
        if(trie[pos].child[s[i]-'a']!=0){
            pos=trie[pos].child[s[i]-'a'];
        }else{
            return 0;
        }
    }
    trie[pos].times++;
    return trie[pos].times;
}

int main(void){
    ios::sync_with_stdio(false);
    int ans=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x;
        insert(x);
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>x;
        ans=find(x);
        if(ans==0) printf("WRONG\n");
        else if(ans==1) printf("OK\n");
        else if(ans>=2) printf("REPEAT\n");
    }    
}