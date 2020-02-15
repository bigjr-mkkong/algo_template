#include <bits/stdc++.h>
#define tdown 0.996;
using namespace std;
struct node{
	int x,y,w;
};
int n;
node obj[2050];
double ansx,ansy,answ;
double energy(double x,double y){
	double r=0,dx,dy;
	for(int i=1;i<=n;i++){
		dx=x-obj[i].x;
		dy=y-obj[i].y;
		r+=sqrt(dx*dx+dy*dy)*obj[i].w;
	}
	return r;
}
void sa(){
	double tmpe=4000;
	while(tmpe>1e-15){
		double ex=ansx+(rand()*2-RAND_MAX)*tmpe;
		double ey=ansy+(rand()*2-RAND_MAX)*tmpe;
		double ew=energy(ex,ey);
		double de=ew-answ;
		if(de<0){
			ansx=ex;ansy=ey;answ=ew;
		}else if(exp(-de/tmpe)*RAND_MAX>rand()){
			ansx=ex;ansy=ey;
		}
		tmpe*=tdown;
	}
}
int main(void){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d %d %d",&obj[i].x,&obj[i].y,&obj[i].w);
		ansx+=obj[i].x;
		ansy+=obj[i].y;
	}
	ansx/=n;
	ansy/=n;
	answ=energy(ansx,ansy);
	sa();
	printf("%.3f %.3f\n",ansx,ansy);
}
