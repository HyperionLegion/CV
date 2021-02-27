#include <iostream>
#include "stdio.h"
#include<ctime> 
#include <math.h>       /* pow */
#include <algorithm>    // std::min
#include <fstream>


int m[800][800][3]; //matrix for pixles
void drawLine(int x, int y, int xs, int ys); //method for lines
void drawCircle(int xcint, int ycint, double radius); //method for circles
using namespace std;
int main(){
    ofstream myfile;
    myfile.open("triangle.ppm"); //write to triangle.ppm
    myfile<<"P3  800  800  1\n";
    for (int i = 0; i < 800; i++) 
        for (int j = 0; j < 800; j++) {
            m[i][j][0]=1, m[i][j][1]=1, m[i][j][2]=1;//i = rows (up and down), j = columns (left and right)
        }
    srand(time(0));
    //generate random points every time
    double xr1=(double)rand()/RAND_MAX, xr2=(double)rand()/RAND_MAX, xr3=(double)rand()/RAND_MAX, yr1=(double)rand()/RAND_MAX, yr2=(double)rand()/RAND_MAX, yr3=(double)rand()/RAND_MAX;
    
    int x1 =int(xr1*800.0+0.5);
    int y1 =int(yr1*800.0+0.5);
    int x2 =int(xr2*800.0+0.5);
    int y2 =int(yr2*800.0+0.5);
    int x3 =int(xr3*800.0+0.5);
    int y3 =int(yr3*800.0+0.5);
    /*int x1 = 0, y1=400, x2=400,y2=400,x3=400,y3=0;
    xr1 = 0.0/800, yr1=400.0/800, xr2=400.0/800,yr2=400.0/800,xr3=400.0/800,yr3=0.0/800;//hardcode tests*/

    
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
    double xc, yc;
    if(yr2-yr1==0){
        xc = (xr1*800+xr2*800)/2;
        yc = (yr2*800+yr3*800)/2 - (xr3*800-xr2*800)/(yr3*800-yr2*800)*(xc-(xr2*800+xr3*800)/2); //y coord of center of circles
    }
    else if(yr3-yr2==0){
        xc = (xr3*800+xr2*800)/2;
        yc = (yr1*800+yr2*800)/2 - (xr2*800-xr1*800)/(yr2*800-yr1*800)*(xc-(xr1*800+xr2*800)/2); //y coord of center of circles
    }
    else{
    xc = ((yr1*800+yr2*800)/2 - (yr2*800+yr3*800)/2 + ((xr2*800-xr1*800)/(yr2*800-yr1*800) *(xr1*800+xr2*800)/2) - ((xr3*800-xr2*800)/(yr3*800-yr2*800) *(xr2*800+xr3*800)/2))/(-(xr3*800-xr2*800)/(yr3*800-yr2*800) + (xr2*800-xr1*800)/(yr2*800-yr1*800));//x coord of center of circles
    yc = (yr1*800+yr2*800)/2 - (xr2*800-xr1*800)/(yr2*800-yr1*800)*(xc-(xr1*800+xr2*800)/2); //y coord of center of circles
    }

    int xcint = int(xc+0.5);
    int ycint = int(yc+0.5);
    double radius1 = sqrt(pow(xc-xr1*800, 2)+pow(yc-yr1*800,2));
    //drawing circle (can turn into a method later)
    drawCircle(xcint, ycint, radius1);
    double xi1, xi2, xi3, yi1, yi2, yi3;
        xi1 = xr1*800;
        yi1 = yr1*800;
        xi2 = xr2*800;
        yi2 = yr2*800;
        xi3 = xr3*800;
        yi3 = yr3*800;
   

    double a =sqrt(pow(xi3-xi2, 2)+pow(yi3-yi2,2)),b =sqrt(pow(xi1-xi3, 2)+pow(yi1-yi3, 2)),c=sqrt(pow(xi2-xi1, 2)+pow(yi2-yi1,2));
    double s = 0.5 * (a+b+c);
    double xi = (a*xi1+b*xi2+c*xi3)/(2*s);
    double yi = (a*yi1+b*yi2+c*yi3)/(2*s);
    double radius2 = sqrt((s-a)*(s-b)*(s-c)/s);
    int xint  = int(xi+0.5);
    int yint =  int(yi+0.5);
    drawCircle(xint, yint, radius2);//incircle
 
    //9 point circle
    double xo, yo;
    if(yi2-yi1==0){
        xo=xi3;
        yo=yi1 - (xi3-xi2)/(yi3-yi2)*(xo-xi1);
    }
    else if(yi3-yi2==0){
        xo=xi1;
        yo=yi1 - (xi3-xi2)/(yi3-yi2)*(xo-xi1);
    }
    else{
    xo = (yi3-yi1+(xi2-xi1)/(yi2-yi1)*xi3-(xi3-xi2)/(yi3-yi2)*xi1)/((xi2-xi1)/(yi2-yi1) - (xi3-xi2)/(yi3-yi2));
    yo = yi1 - (xi3-xi2)/(yi3-yi2)*(xo-xi1);
    }
    double x9 = (xo+xc)/2;
    double y9 = (yo+yc)/2;
    double radius3 = radius1 / 2.0;
    drawCircle(int(x9+0.5), int(y9+0.5), radius3);

    //euler line
    double startx, starty, endx, endy;
    double slope;
    double centroidx = xo;
    double centroidy = yo;
    if(int(centroidx+0.5)-int(xc+0.5)==0){
        startx=centroidx;
        endx=centroidx;
        starty=799;
        endy=0;
    }
    else if(int(centroidy+0.5)-int(yc+0.5)==0){
        starty=centroidy;
        endy=centroidy;
        startx=0;
        endx=799;
    }
    else{
    slope = (centroidy-yc)/(centroidx-xc);
    if(yc+slope*(799-xc)>=0&& yc+slope*(799-xc)<=799){
        endx = 799;
        endy = yc+slope*(799-xc);
    }
    else if(yc+slope*(799-xc)>799){
        endy=799;
        endx= (endy-yc)/slope +xc;
    }
    else if(yc+slope*(799-xc)<0){
        endy=0;
        endx = (endy-yc)/slope+xc;
    }
    if(yc+slope*(0-xc)>=0&& yc+slope*(0-xc)<=799){
        startx = 0;
        starty = yc+slope*(0-xc);
    }
    else if(yc+slope*(0-xc)>799){
        starty=799;
        startx= (starty-yc)/slope +xc;
    }
    else if(yc+slope*(799-xc)<0){
        starty=0;
        startx = (starty-yc)/slope+xc;
    }
    }
    drawLine(int(startx+0.5), int(starty+0.5), int(endx+0.5), int(endy+0.5)); 
    //write into ppm file
    for (int i = 0; i < 800; i++) {
    	for (int j =0; j <  800; j++)
            for(int k=0; k<3;k++)
                myfile<<m[i][j][k]<<' ';
        myfile<<"\n";
    }
    myfile.close();
    return 0;
}
void drawLine(int x, int y, int xs, int ys){
if(x==xs){
    for(int b =std::min(y, ys); b<=std::max(y,ys); b++){
        m[b][x][0]=0,m[b][x][1]=0,m[b][x][2]=0;
    }
}
else if(y==ys){
    for(int b =std::min(x, xs); b<=std::max(x,xs); b++){
        m[y][b][0]=0,m[y][b][1]=0,m[y][b][2]=0;
    }
}
else{
    if (abs(xs-x)>=abs(ys-y)){ //x is driving axis
    int xl, yl, xr, yr; //coords of left x and y, right x and y
    if(xs>=x){ //P1 is the left coord
        xl = x;
        yl = y;
        xr =xs;
        yr =ys;
    }
    else{ //P2 is the left coord
        xl = xs;
        yl = ys;
        xr = x;
        yr = y;
    }
    int dx1= xr-xl, dy1 = yr-yl;
        int e;
        if(dy1>0)
            e = dy1-dx1;
        else
        {
           e = dy1 + dx1;
        }
        
        int j = yl;
         for (int i=xl; i<=xr; i++){
             m[j][i][0] = 0, m[j][i][1] = 0,m[j][i][2] = 0;
             if(dy1>=0){
             if(e>=0){
                 j+=1;
                 e-=dx1;
             }
             }
             else{
                 if(e<=0){
                     j-=1;
                     e+=dx1;
                 }
             }
             e += dy1;
         }
    }
    else{//y is driving axis
        int xt, yt, xb, yb; //coords of bottom x and y, top x and y
    if(ys<y){ //P2 is the top coord
        xb = x;
        yb = y;
        xt =xs;
        yt =ys;
    }   
    else{ //P2 is the bottom coord
        xb = xs;
        yb = ys;
        xt = x;
        yt = y;
    }
    int dx1= xt-xb, dy1 = yt-yb, i=xb;
         int e;
        if(dx1>=0)
            e = dx1+dy1;
        else
        {
           e = -dy1 + dx1;
        }
        
         for (int j=yb; j>=yt; j--){
             m[j][i][0] = 0, m[j][i][1] = 0,m[j][i][2] = 0;
             if(dx1>=0){
             if(e>=0){
                 i+=1;
                 e+=dy1;
             }
             }
             else{
                 if(e<=0){
                     i-=1;
                     e-=dy1;
                 }
             }
             e += dx1;
         }
    }
}
}
void drawCircle(int xcint, int ycint, double radius){
    int a, b, xmax, b2, b2_new, tb;
    xmax = int(radius*0.70710678+0.5);
    b = int(radius+0.5);
    b2 = b*b;
    tb = (2*b)-1;
    b2_new = b2;
    for(a = 0; a<=xmax+1; a++){
        if(b2-b2_new>=tb){
            b2 -=tb;
            b-=1;
            tb-=2;
        }
            if(ycint+b<800&&xcint+a<800&&ycint+b>=0&&xcint+a>=0)
            m[ycint+b][xcint+a][0]=0,m[ycint+b][xcint+a][1]=0,m[ycint+b][xcint+a][2]=0;
            if(ycint-b>=0&&xcint+a<800&&ycint-b<800&&xcint+a>=0)
            m[ycint-b][xcint+a][0]=0,m[ycint-b][xcint+a][1]=0,m[ycint-b][xcint+a][2]=0;
            if(ycint+b<800&&xcint-a>=0&&ycint+b>=0&&xcint-a<800)
            m[ycint+b][xcint-a][0]=0,m[ycint+b][xcint-a][1]=0,m[ycint+b][xcint-a][2]=0;
            if(ycint-b>=0&&xcint-a>=0&&ycint-b<800&&xcint-a<800)
            m[ycint-b][xcint-a][0]=0,m[ycint-b][xcint-a][1]=0,m[ycint-b][xcint-a][2]=0;
            if(ycint+a<800&&xcint+b<800&&ycint+a>=0&&xcint+b>=0)
            m[ycint+a][xcint+b][0]=0,m[ycint+a][xcint+b][1]=0,m[ycint+a][xcint+b][2]=0;
            if(ycint-a>=0&&xcint+b<800&&ycint-a<800&&xcint+b>=0)
            m[ycint-a][xcint+b][0]=0,m[ycint-a][xcint+b][1]=0,m[ycint-a][xcint+b][2]=0;
            if(ycint+a<800&&xcint-b>=0&&ycint+a>=0&&xcint-b<800)
            m[ycint+a][xcint-b][0]=0,m[ycint+a][xcint-b][1]=0,m[ycint+a][xcint-b][2]=0;
            if(ycint-a>=0&&xcint-b>=0&&ycint-a<800&&xcint-b<800)
            m[ycint-a][xcint-b][0]=0,m[ycint-a][xcint-b][1]=0,m[ycint-a][xcint-b][2]=0;
        
        b2_new -=(2*a)-3;
    }
}