#include <iostream>
#include "stdio.h"
#include<ctime> 
#include <math.h>       /* pow */
#include <algorithm>    // std::min
#include <fstream>
#include <iomanip>      // std::setprecision
#include <string>

int m[800][800][3]; //matrix for pixles
double points[48] = {};
double areas[6] = {};
void makeSquare(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, int count);
void drawLine(int x, int y, int xs, int ys); //method for lines
void drawCircle(int xcint, int ycint, double radius); //method for circles
double* endPoints(double x, double y, double xs, double ys);
bool checkOutside(double x1, double y1,double x2, double y2, double x3,double y3, double x4, double y4);
void part1();
void part2();

using namespace std;
int main(){
    part1();
    part2();
    return 0;
}
void part2(){
    string line;
    ifstream myfile ("points.txt");
    if(myfile.is_open()){
        getline(myfile, line);
    }
    myfile.close();
    double x1 = std::stod(line.substr(line.find("(")+1, line.find(",")));
    line = line.substr(line.find(","));
    double y1 = std::stod(line.substr(line.find(",")+1,line.find(")")));
   line = line.substr(line.find("("));
    double x2 = std::stod(line.substr(line.find("(")+1,line.find(",")));
    line = line.substr(line.find(","));
    double y2 = std::stod(line.substr(line.find(",")+1,line.find(")")));
    line = line.substr(line.find("("));
    double x3 = std::stod(line.substr(line.find("(")+1,line.find(",")));
    line = line.substr(line.find(","));
    double y3 = std::stod(line.substr(line.find(",")+1,line.find(")")));
    line = line.substr(line.find("("));
    double x4 = std::stod(line.substr(line.find("(")+1,line.find(",")));
    line = line.substr(line.find(","));
    double y4 = std::stod(line.substr(line.find(",")+1,line.find(")")));
    makeSquare(x1, y1, x2, y2, x3, y3, x4, y4, 0);
    makeSquare(x1, y1, x3, y3, x2, y2, x4, y4, 2);
    makeSquare(x1, y1, x4, y4, x3, y3, x2, y2, 4);
    int min=0;
    for (int i =0; i<6; i++)
        if(areas[min]>areas[i])
            min = i;

    
    double *p1 = endPoints(points[8*min], points[8*min+1],points[8*min+2],points[8*min+3]);
    double e1[4] = {p1[0], p1[1], p1[2], p1[3]};
    double *p2 = endPoints(points[8*min], points[8*min+1],points[8*min+4],points[8*min+5]);
    double e2[4] = {p2[0], p2[1], p2[2], p2[3]};
    double *p3 = endPoints(points[8*min+2], points[8*min+3],points[8*min+6],points[8*min+7]);
    double e3[4] = {p3[0], p3[1], p3[2], p3[3]};
    double *p4 = endPoints(points[8*min+4], points[8*min+5],points[8*min+6],points[8*min+7]);
    double e4[4] = {p4[0], p4[1], p4[2], p4[3]};
    std::ofstream out("output.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf());
    std::cout << std::fixed;
    cout << std::setprecision(17) << "("<<x1<<","<<y1<<") , " << "("<<x2<<","<<y2<<") , " <<"("<<x3<<","<<y3<<") , " <<"("<<x4<<","<<y4<<")";
    cout<< "\n";
    for(int i=0; i<6; i++){
        for(int j =0; j<6; j=j+2){
            cout << std::setprecision(17) << "("<<points[8*i+j] << ","<<points[8*i+j+1]<<") , ";
        }
        cout<<std::setprecision(17)<<"("<<points[8*i+6] <<","<<points[8*i+7]<<") Area = " <<areas[i];
        cout <<"\n";
    }
    std::cout.rdbuf(coutbuf); //reset to standard output again*/
    ofstream myfile2;
    myfile2.open("output.ppm"); //write to triangle.ppm
    myfile2<<"P3  800  800  1\n";
    for (int i = 0; i < 800; i++) 
        for (int j = 0; j < 800; j++) {
            m[i][j][0]=1, m[i][j][1]=1, m[i][j][2]=1;//i = rows (up and down), j = columns (left and right)
        }
    drawCircle(int(x1*800.0+0.5), int(y1*800.0+0.5), 2);
    drawCircle(int(x2*800.0+0.5), int(y2*800.0+0.5), 2);
    drawCircle(int(x3*800.0+0.5), int(y3*800.0+0.5), 2);
    drawCircle(int(x4*800.0+0.5), int(y4*800.0+0.5), 2);
    drawCircle(int(points[8*min]*800.0+0.5), int(points[8*min+1]*800.0+0.5), 2);
    drawCircle(int(points[8*min+2]*800.0+0.5), int(points[8*min+3]*800.0+0.5), 2);
    drawCircle(int(points[8*min+4]*800.0+0.5), int(points[8*min+5]*800.0+0.5), 2);
    drawCircle(int(points[8*min+6]*800.0+0.5), int(points[8*min+7]*800.0+0.5), 2);
    for(int x =0; x<4; x++){
         if(int(800.0*e1[x]+0.5)>=800){
             e1[x]=799;
         }
         else{
             e1[x] = int(800.0*e1[x]+0.5);
         }
    }
    for(int x =0; x<4; x++){
         if(int(800.0*e2[x]+0.5)>=800){
             e2[x]=799;
         }
         else{
             e2[x] = int(800.0*e2[x]+0.5);
         }
    }
    for(int x =0; x<4; x++){
         if(int(800.0*e3[x]+0.5)>=800){
             e3[x]=799;
         }
         else{
             e3[x] = int(800.0*e3[x]+0.5);
         }
    }
    for(int x =0; x<4; x++){
         if(int(800.0*e4[x]+0.5)>=800){
             e4[x]=799;
         }
         else{
             e4[x] = int(800.0*e4[x]+0.5);
         }
    }   
    drawLine(e1[0], e1[1], e1[2], e1[3]);
    drawLine(e2[0], e2[1], e2[2], e2[3]);
    drawLine(e3[0], e3[1], e3[2], e3[3]);
    drawLine(e4[0], e4[1], e4[2], e4[3]);
    for (int i = 0; i < 800; i++) {
    	for (int j =0; j <  800; j++)
            for(int k=0; k<3;k++)
                myfile2<<m[i][j][k]<<' ';
        myfile2<<"\n";
    }
    myfile2.close();
}
void makeSquare(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, int count){
    double slope, ex1, ex2, ey1, ey2;
    if(x2!=x1&&y2!=y1){
    slope = (y2-y1)/(x2-x1);
    double dist = sqrt(pow(x1-x2,2)+pow(y1-y2, 2));
    double a = (1+1/pow(slope,2));
    double b = (-2*x3 - 2*x3/(pow(slope,2)));
    double c = (pow(x3,2)+pow(x3,2)/pow(slope,2) - pow(dist,2));
    ex1 = (-1*b + sqrt(pow(b, 2) - 4*a*c))/(2*a);
    ex2 = (-1*b - sqrt(pow(b, 2) - 4*a*c))/(2*a);
    ey1 = -1/slope*(ex1-x3) + y3;
    ey2 = -1/slope*(ex2-x3)+y3;   
    }
    else if(x2==x1){
        double dist = sqrt(pow(y1-y2,2));
        ex1 = x3+dist;
        ex2 = x3-dist;
        ey1 = y3;
        ey2 = y3;
    }
    else{
        double dist = sqrt(pow(x1-x2,2));
        ey1 = y3+dist;
        ey2 = y3-dist;
        ex1 = x3;
        ex2 = x3;
    }
    double ix1, iy1, ix2, iy2, ix3, iy3, ix4, iy4;
    if(x4!=ex1&&y4!=ey1){
    slope = (y4-ey1)/(x4-ex1);
    ix1 = (y1 - y4 + slope*x4 + x1/slope)/(slope + 1/slope);
    iy1 = y4 + slope*(ix1-x4);
    ix2 = (y2 -y4 + slope*x4 + x2/slope)/(slope + 1/slope);
    iy2 = y4 + slope*(ix2-x4);
    ix3 = (y1 - y3 + slope*x3 + x1/slope)/(slope + 1/slope);
    iy3 = y3 + slope*(ix3-x3);
    ix4 = (y2 -y3 + slope*x3 + x2/slope)/(slope + 1/slope);
    iy4 =y3 + slope*(ix4-x3);
    }
    else if(x4==ex1){
        ix1 = x4;
        iy1 = y1;
        ix2 = x4;
        iy2 = y2;
        ix3 = x3;
        iy3 = y1;
        ix4 = x3;
        iy4 = y2;
    }
    else{
        ix1 = x1;
        iy1 = y4;
        ix2 = x2;
        iy2 = y4;
        ix3 = x1;
        iy3 = y3;
        ix4 = x2;
        iy4 = y3;
    }
    points[count*8]=ix1, points[count*8+1]=iy1, points[count*8+2]=ix2, points[count*8+3]=iy2, points[count*8+4]=ix3, points[count*8+5]=iy3, points[count*8+6]=ix4, points[count*8+7]=iy4;
    areas[count]=pow(ix1-ix2,2)+pow(iy1-iy2,2);
    
    if(x4!=ex2&&y4!=ey2){
    slope = (y4-ey2)/(x4-ex2);
    ix1 = (y1 - y4 + slope*x4 + x1/slope)/(slope + 1/slope);
    iy1 = y4 + slope*(ix1-x4);
    ix2 = (y2 -y4 + slope*x4 + x2/slope)/(slope + 1/slope);
    iy2 = y4 + slope*(ix2-x4);
    ix3 = (y1 - y3 + slope*x3 + x1/slope)/(slope + 1/slope);
    iy3 = y3 + slope*(ix3-x3);
    ix4 = (y2 -y3 + slope*x3 + x2/slope)/(slope + 1/slope);
    iy4 =y3 + slope*(ix4-x3); 
    }
    else if(x4==ex2){
        ix1 = x4;
        iy1 = y1;
        ix2 = x4;
        iy2 = y2;
        ix3 = x3;
        iy3 = y1;
        ix4 = x3;
        iy4 = y2;
    }
    else{
        ix1 = x1;
        iy1 = y4;
        ix2 = x2;
        iy2 = y4;
        ix3 = x1;
        iy3 = y3;
        ix4 = x2;
        iy4 = y3;
    }
    points[(count+1)*8]=ix1, points[(count+1)*8+1]=iy1, points[(count+1)*8+2]=ix2, points[(count+1)*8+3]=iy2, points[(count+1)*8+4]=ix3, points[(count+1)*8+5]=iy3, points[(count+1)*8+6]=ix4, points[(count+1)*8+7]=iy4;
    areas[(count+1)]=pow(ix1-ix2,2)+pow(iy1-iy2,2);
}
double* endPoints(double x, double y, double xs, double ys){
    double slope;
    double startx, endx, starty, endy;
    if(x-xs==0){
        startx=x;
        endx=x;
        starty=0;
        endy=1;
    }
    else if(y-ys==0){
        starty=y;
        endy=y;
        startx=0;
        endx=1;
    }
    else{
    slope = (y-ys)/(x-xs);
    if(ys+slope*(1-xs)>=0&& ys+slope*(1-xs)<=1){
        endx = 1;
        endy = ys+slope*(1-xs);
    }
    else if(ys+slope*(1-xs)>1){
        endy=1;
        endx= (endy-ys)/slope +xs;
    }
    else if(ys+slope*(1-xs)<0){
        endy=0;
        endx = (endy-ys)/slope+xs;
    }
    if(ys+slope*(0-xs)>=0&& ys+slope*(0-xs)<=1){
        startx = 0;
        starty = ys+slope*(0-xs);
    }
    else if(ys+slope*(0-xs)>1){
        starty=1;
        startx= (starty-ys)/slope +xs;
    }
    else if(ys+slope*(0-xs)<0){
        starty=0;
        startx = (starty-ys)/slope+xs;
    }
    }
    static double arr[4];
    arr[0] = startx, arr[1]=starty, arr[2]=endx, arr[3]=endy;
    return arr;
}
void part1(){
    std::ofstream out("points.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf());

    srand(time(0));
    //generate random points every time
    double xr1=(double)rand()/RAND_MAX, xr2=(double)rand()/RAND_MAX, xr3=(double)rand()/RAND_MAX, yr1=(double)rand()/RAND_MAX, yr2=(double)rand()/RAND_MAX, yr3=(double)rand()/RAND_MAX;
    //double xr1 = 0.0, yr1=0.0, xr2 = 0.0, yr2=1.0, xr3 = 1.0, yr3=0.0; //test cases
    while((xr1==xr2&&xr2==xr3)||(yr1==yr2&&yr2==yr3)){
        xr1=(double)rand()/RAND_MAX, xr2=(double)rand()/RAND_MAX, xr3=(double)rand()/RAND_MAX, yr1=(double)rand()/RAND_MAX, yr2=(double)rand()/RAND_MAX, yr3=(double)rand()/RAND_MAX;
    }
   
    double xr4, yr4;
    bool outside = false;
    while(!outside){
        xr4=(double)rand()/RAND_MAX, yr4=(double)rand()/RAND_MAX;
        outside = checkOutside(xr1, yr1, xr2, yr2, xr3, yr3, xr4,yr4) && checkOutside(xr1, yr1, xr2, yr2, xr4, yr4, xr3, yr3) && checkOutside(xr1, yr1, xr3, yr3, xr4, yr4, xr2, yr2) && checkOutside(xr2, yr2, xr3, yr3, xr4, yr4, xr1, yr1); //test each triangle
    }
    //xr4 = 1.0, yr4 = 1.0;
    std::cout << std::fixed;
    cout << std::setprecision(17) << "("<<xr1<<","<<yr1<<") , " << "("<<xr2<<","<<yr2<<") , " <<"("<<xr3<<","<<yr3<<") , " <<"("<<xr4<<","<<yr4<<")";
    std::cout.rdbuf(coutbuf); //reset to standard output again
}
bool checkOutside(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){//check if point 4 is outside
    if(x1==x2&&(x4-x1)*(x3-x1)<0){
        return true;
    }
    else if(x2==x3&&(x4-x2)*(x1-x2)<0){
return true;
    }
    else if(x3==x1&&(x4-x1)*(x2-x1)<0){
return true;
    }
    
    else{
    if((y3 - (y1+(y2-y1)/(x2-x1)*(x3-x1)))*(y4 - (y1+(y2-y1)/(x2-x1)*(x4-x1)))<0){
        return true;
    }
    if((y2 - (y1+(y3-y1)/(x3-x1)*(x2-x1)))*(y4 - (y1+(y3-y1)/(x3-x1)*(x4-x1)))<0){
        return true;
    }
    if((y1 - (y2+(y3-y2)/(x3-x2)*(x1-x2)))*(y4 - (y2+(y3-y2)/(x3-x2)*(x4-x2)))<0){
        return true;
    }
    }
    return false;
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