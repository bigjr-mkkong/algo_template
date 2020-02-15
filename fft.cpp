#include<bits/stdc++.h>
#define maxn 2621450
#define pi acos(-1)
using namespace std;
typedef complex<double> cp;
int n,m,l,r[maxn];
cp a[maxn],b[maxn];
void fft(cp *a,int f){
    for(int i=0;i<n;i++)if(i<r[i])swap(a[i],a[r[i]]);
    for(int i=1;i<n;i<<=1){
        cp wn(cos(pi/i),f*sin(pi/i));
        for(int p=i<<1,j=0;j<n;j+=p){
            cp w(1,0);
            for(int k=0;k<i;k++,w*=wn){
                cp x=a[j+k],y=w*a[j+k+i];
                a[j+k]=x+y;a[j+k+i]=x-y;
            }
        }
    }
}
int main(){
    int ia,ib;
    scanf("%d %d",&n,&m);
    for(int i=0;i<=n;i++){
        scanf("%d",&ia);
        a[i]=ia;
    } 
    for(int i=0;i<=m;i++){
        scanf("%d",&ib);
        b[i]=ib;
    }
    m+=n;
    for(n=1;n<=m;n<<=1)l++;
    for(int i=0;i<n;i++)r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
    fft(a,1);fft(b,1);
    for(int i=0;i<=n;i++)a[i]=a[i]*b[i];
    fft(a,-1);
    for(int i=0;i<=m;i++)printf("%d ",(int)(a[i].real()/n+0.5));
}
