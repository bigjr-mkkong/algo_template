#include <bits/stdc++.h>
using namespace std;
#define RED     1
#define BLACK   0

const int maxn=1926;
struct node{
    int fa;
    int ch[2];
    int val=NULL;
    int color;
}rbt[maxn];
int ptr=0,root=1;

void insertFix(int pos);

int newnode(int val){
    ptr++;
    rbt[ptr].val=val;
    rbt[ptr].color=RED;
    return ptr;
}

int ischild(int x){//which child x is to its father
    return rbt[rbt[x].fa].ch[1]==x;
}

void rotateL(int a){
    int b=rbt[a].ch[1];
    int fa=rbt[a].fa;
    int k=ischild(a);
    if(root==a) root=rbt[a].ch[1];
    rbt[a].ch[1]=rbt[b].ch[0];
    rbt[rbt[b].ch[0]].fa=a;
    rbt[b].ch[0]=a;
    rbt[a].fa=b;
    rbt[fa].ch[k]=b;
    rbt[b].fa=fa;
}

void rotateR(int a){
    int b=rbt[a].ch[0];
    int fa=rbt[a].fa;
    int k=ischild(a);
    if(root==a) root=rbt[a].ch[0];
    rbt[a].ch[0]=rbt[b].ch[1];
    rbt[rbt[b].ch[1]].fa=a;
    rbt[b].ch[1]=a;
    rbt[a].fa=b;
    rbt[fa].ch[k]=b;
    rbt[a].fa=b;
}

int _insert(int pos,int val,int fa){
    int t;
    if(rbt[pos].val==NULL){
        int tmp=newnode(val);
        if(rbt[fa].val>val) rbt[fa].ch[0]=tmp;
        else rbt[fa].ch[1]=tmp;
        rbt[tmp].fa=fa;
        return tmp;
    }

    if(rbt[pos].val>val){
        rbt[pos].ch[0]=_insert(rbt[pos].ch[0],val,pos);
        t=rbt[pos].ch[0];
    }else{
        rbt[pos].ch[1]=_insert(rbt[pos].ch[1],val,pos);
        t=rbt[pos].ch[1];
    }
    return pos;
}

int findNode(int pos,int val){
    if(rbt[pos].val==val) return pos;

    if(rbt[pos].val>val) return findNode(rbt[pos].ch[0],val);
    else return findNode(rbt[pos].ch[1],val);
}

int insert(int val){
    _insert(root,val,0);
    int k=findNode(root,val);
    insertFix(k);
}

void insertFix(int pos){
    int fa,gfa;
    while((fa=rbt[pos].fa)!=0&&rbt[fa].color==RED){
        gfa=rbt[fa].fa;
        if(ischild(fa)==0){
            int uncle=rbt[gfa].ch[1];
            if(rbt[uncle].color==RED&&rbt[uncle].val!=NULL){
                rbt[uncle].color=BLACK;
                rbt[fa].color=BLACK;
                rbt[gfa].color=RED;
                pos=gfa;
                continue;
            }else if(rbt[uncle].color==BLACK&&ischild(pos)==1){
                rotateR(fa);
                swap(rbt[fa],rbt[pos]);
            }

            rbt[fa].color=BLACK;
            rbt[gfa].color=RED;
            rotateR(gfa);
        }else{
            int uncle=rbt[gfa].ch[0];
            if(rbt[uncle].val!=NULL&&rbt[uncle].color==RED){
                rbt[uncle].color=BLACK;
                rbt[fa].color=BLACK;
                rbt[gfa].color=RED;
                pos=gfa;
                continue;
            }else if(rbt[uncle].color==BLACK&&ischild(pos)==0){
                rotateR(fa);
                swap(rbt[fa],rbt[pos]);
            }

            rbt[fa].color=BLACK;
            rbt[gfa].color=RED;
            rotateL(gfa);
            
        }
    }
    rbt[root].color=BLACK;
}

int main(void){
    for(int i=1;i<=10;i++) 
        insert(i);
}