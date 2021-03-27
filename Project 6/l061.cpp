//atan 2 (GY/GX) convert radians to degrees

//double threshold (no edge, weak edge, strong edge) image 2
//transform magnitude matrix into double threshold matrix (values of 0, 1, 2)
//promote any weak edges (1) to a strong edge if connected to a strong edge (or chain of weak edges eventually reach strong edge)
//AREA FILL ^^
//then 2 -> 1 rest is 0 for ppm (hysteris)


//non maximum supression image 1
//each pixel look at the angle corresponding and round
//round by adding (45/2 to angle) / 45 then multiply by 45
//look at neighbor pixels in that direction and see if that pixel is the maximum in the magnitude matrix 
//p >= l1 and p>= l2


//take hysteris and non max supression matrices and if they are both 1 and 1 then it is 1
//else it is 0
#include <iostream>
#include "stdio.h"
#include<ctime> 
#include <math.h>       /* pow */
#include <fstream>
#include <iterator>
#include <iomanip>      // std::setprecision
#include <vector> 
#include <chrono> 
#include <bits/stdc++.h>

using namespace std;
void drawCircle(double x, double y, int colors[3]){ //draw circle of 2 with specified color at the x and y coordinate
            //colors is an array of 3 ints to represent RGB for drawing
            int xcint = int(800.0*x+0.5);
            int ycint = int(800.0*y+0.5);
            int radius = 2;
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
                    m[ycint+b][xcint+a][0]=colors[0],m[ycint+b][xcint+a][1]=colors[1],m[ycint+b][xcint+a][2]=colors[2];
                    if(ycint-b>=0&&xcint+a<800&&ycint-b<800&&xcint+a>=0)
                    m[ycint-b][xcint+a][0]=colors[0],m[ycint-b][xcint+a][1]=colors[1],m[ycint-b][xcint+a][2]=colors[2];
                    if(ycint+b<800&&xcint-a>=0&&ycint+b>=0&&xcint-a<800)
                    m[ycint+b][xcint-a][0]=colors[0],m[ycint+b][xcint-a][1]=colors[1],m[ycint+b][xcint-a][2]=colors[2];
                    if(ycint-b>=0&&xcint-a>=0&&ycint-b<800&&xcint-a<800)
                    m[ycint-b][xcint-a][0]=colors[0],m[ycint-b][xcint-a][1]=colors[1],m[ycint-b][xcint-a][2]=colors[2];
                    if(ycint+a<800&&xcint+b<800&&ycint+a>=0&&xcint+b>=0)
                    m[ycint+a][xcint+b][0]=colors[0],m[ycint+a][xcint+b][1]=colors[1],m[ycint+a][xcint+b][2]=colors[2];
                    if(ycint-a>=0&&xcint+b<800&&ycint-a<800&&xcint+b>=0)
                    m[ycint-a][xcint+b][0]=colors[0],m[ycint-a][xcint+b][1]=colors[1],m[ycint-a][xcint+b][2]=colors[2];
                    if(ycint+a<800&&xcint-b>=0&&ycint+a>=0&&xcint-b<800)
                    m[ycint+a][xcint-b][0]=colors[0],m[ycint+a][xcint-b][1]=colors[1],m[ycint+a][xcint-b][2]=colors[2];
                    if(ycint-a>=0&&xcint-b>=0&&ycint-a<800&&xcint-b<800)
                    m[ycint-a][xcint-b][0]=colors[0],m[ycint-a][xcint-b][1]=colors[1],m[ycint-a][xcint-b][2]=colors[2];
                
                b2_new -=(2*a)-3;
            }
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
void part1(){
    int r,g, b;
    ifstream infile("image.ppm");
    string line;
    getline(infile, line);
    getline(infile, line);

     const int width = std::stoi(line.substr(0,line.find(" ")));
     const int height = std::stoi(line.substr(line.find(" ")+1));

    int ***grey = new int**[width];
    for(int i=0;i<width;i++){
        grey[i] = new int*[height];
        for(int j =0; j<height; j++){
            grey[i][j] = new int[3];
        }
    }
     int ***binary = new int**[width];
    for(int i=0;i<width;i++){
        binary[i] = new int*[height];
        for(int j =0; j<height; j++){
            binary[i][j] = new int[3];
        }
    }
    double **angle = new double*[width];
    for(int i=0;i<width;i++){
        angle[i] = new double[height];
    }

    getline(infile, line);
    int count = 0;
    while(getline(infile, line)){ //fill grey matrix
        while(line.length()>1){
            r = std::stoi(line.substr(0, line.find(" ")));
            line = line.substr(line.find(" ")+1);
            g = std::stoi(line.substr(0, line.find(" ")));
            line = line.substr(line.find(" ")+1);
            b = std::stoi(line.substr(0, line.find(" ")));
            line = line.substr(line.find(" ")+1);
            grey[count%(width)][count/width][0] = (r+g+b)/3;
            grey[count%(width)][count/width][1] = (r+g+b)/3;
            grey[count%(width)][count/width][2] = (r+g+b)/3;
            count++;
        }
    }
    ofstream myfile;
        myfile.open("imageg.ppm"); //write to output.ppm
        myfile<<"P3 "<<  width << " " << height << " "<< "255\n";
        for (int i = 0; i < height; i++) {
            for (int j =0; j <  width; j++)
                for(int k=0; k<3;k++)
                    myfile<<grey[j][i][k]<<' ';
            myfile<<"\n";
        }
        myfile.close();
    int derivY[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int derivX[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for(int x=1; x<width-1; x++){
        for(int y=1; y<height-1;y++){
            int yvalue = 0;
            int xvalue = 0;
            for(int i=-1;i<2;i++){
                for(int j=-1;j<2;j++){
                    xvalue += grey[i+x][j+y][0]*derivX[i+1][j+1];
                    yvalue += grey[i+x][j+y][0]*derivY[i+1][j+1];
                }
            }
            binary[x][y][0] = sqrt(pow(xvalue, 2) + pow(yvalue, 2));
            binary[x][y][1] = sqrt(pow(xvalue, 2) + pow(yvalue, 2));
            binary[x][y][2] = sqrt(pow(xvalue, 2) + pow(yvalue, 2));
            angle[x][y] = atan2(yvalue, xvalue) * 180/3.14159265358979;
        }
    }
    for(int x =0; x<width; x++){ //fill the borders with 0s
        binary[x][0][0] = 0;
        binary[x][0][1] = 0;
        binary[x][0][2] = 0;
    }
    for(int y=0; y<height; y++){
        binary[0][y][0]=0;
        binary[0][y][1]=0;
        binary[0][y][2]=0;
    }
    //hystheris
    int ***h = new int**[width];
    for(int i=0;i<width;i++){
        h[i] = new int*[height];
        for(int j =0; j<height; j++){
            h[i][j] = new int[3];
        }
    }
    const int low = 200;
    const int high = 300;
    for(int x=0; x<width; x++){
        for(int y=0; y<height; y++){
            if(binary[x][y][0]>=high){
                h[x][y][0] = 2;
                h[x][y][1] = 2;
                h[x][y][2] = 2;
            }
            else if(binary[x][y][0]>=low && binary[x][y][0]<high){
                h[x][y][0] = 1;
                h[x][y][1] = 1;
                h[x][y][2] = 1;
            }
            else{
                h[x][y][0] = 0;
                h[x][y][1] = 0;
                h[x][y][2] = 0;
            }
        }
    }
    //area fill
    int ***prev = new int**[width];
    for(int i=0;i<width;i++){
        prev[i] = new int*[height];
        for(int j =0; j<height; j++){
            prev[i][j] = new int[3];
            prev[i][j][0] = h[i][j][0];
            prev[i][j][1] = h[i][j][0];
            prev[i][j][2] = h[i][j][0];
        }
    }
    bool done = false;
    while(!done){
        done = true;
        for(int x =0; x<width; x++){
            for(int y=0; y<height;y++){
                if(h[x][y][0]==2){
                    if(x+1<width){
                        if(h[x+1][y][0]==1){
                            h[x+1][y][0]=2;
                            h[x+1][y][1]=2;
                            h[x+1][y][2]=2;
                            done = false;
                        }
                        if(y+1<height){
                            if(h[x+1][y+1][0]==1){
                                h[x+1][y+1][0]=2;
                                h[x+1][y+1][1]=2;
                                h[x+1][y+1][2]=2;
                                done = false;
                            }
                        }
                        if(y-1>=0){
                            if(h[x+1][y-1][0]==1){
                                h[x+1][y-1][0]=2;
                                h[x+1][y-1][1]=2;
                                h[x+1][y-1][2]=2;
                                done = false;
                            }
                        }
                    }
                    if(x-1>=0){
                        if(h[x-1][y][0]==1){
                            h[x-1][y][0]=2;
                            h[x-1][y][1]=2;
                            h[x-1][y][2]=2;
                            done = false;
                        }
                        if(y+1<height){
                            if(h[x-1][y+1][0]==1){
                                h[x-1][y+1][0]=2;
                                h[x-1][y+1][1]=2;
                                h[x-1][y+1][2]=2;
                                done = false;
                            }
                        }
                        if(y-1>=0){
                            if(h[x-1][y-1][0]==1){
                                h[x-1][y-1][0]=2;
                                h[x-1][y-1][1]=2;
                                h[x-1][y-1][2]=2;
                                done = false;
                            }
                        }
                    }
                    if(y+1<height){
                        if(h[x][y+1][0]==1){
                            h[x][y+1][0]=2;
                            h[x][y+1][1]=2;
                            h[x][y+1][2]=2;
                            done = false;
                        }
                    }
                    if(y-1>=0){
                        if(h[x][y-1][0]==1){
                            h[x][y-1][0]=2;
                            h[x][y-1][1]=2;
                            h[x][y-1][2]=2;
                            done = false;
                        }
                    }
                }
            }
        }
    }
    for(int x=0; x<width; x++){
        for(int y=0; y<height; y++){
            if(h[x][y][0]==2){
                h[x][y][0] = 1;
                h[x][y][1] = 1;
                h[x][y][2] = 1;
            }
            else{
                h[x][y][0] = 0;
                h[x][y][1] = 0;
                h[x][y][2] = 0;
            }
        }
    }
        myfile.open("image2.ppm"); //write to output.ppm
        myfile<<"P3 " << width << " " << height << " "<< "1\n";
        for (int i = 0; i < height; i++) {
            for (int j =0; j <  width; j++)
                for(int k=0; k<3;k++)
                    myfile<<h[j][i][k]<<' ';
            myfile<<"\n";
        }
        myfile.close();

    //nonmax supression
    int ***n = new int**[width];
    for(int i=0;i<width;i++){
        n[i] = new int*[height];
        for(int j =0; j<height; j++){
            n[i][j] = new int[3];
        }
    }
    for(int x=1; x<width-1; x++){ //what to do about the very edges of the image for angles and then how does the algo work? straight lines ie
        for(int y=1; y<height-1; y++){
                if(angle[x][y]>=0)
                    angle[x][y] = int(angle[x][y]+(22.5))/45 * 45;
                else
                    angle[x][y] = int(angle[x][y]-(22.5))/45 * 45;
                if(angle[x][y] == 0 || angle[x][y] == 180 || angle[x][y] == -0 || angle[x][y]==-180){
                    if(binary[x][y][0] >= binary[x-1][y][0] && binary[x][y][0] >= binary[x+1][y][0]){
                        n[x][y][0] = 1;
                        n[x][y][1] = 1;
                        n[x][y][2] = 1;
                    }
                }
                else if (angle[x][y]==45 || angle[x][y]== -135){
                    //diagnol comparison up right
                    if(binary[x][y][0] >= binary[x+1][y+1][0] && binary[x][y][0] >= binary[x-1][y-1][0]){
                        n[x][y][0] = 1;
                        n[x][y][1] = 1;
                        n[x][y][2] = 1;
                    }
                }
                else if(angle[x][y] == 135 || angle[x][y] == -45){
                    //diagnol comparison up left
                    if(binary[x][y][0] >= binary[x-1][y+1][0] && binary[x][y][0] >= binary[x+1][y-1][0]){
                        n[x][y][0] = 1;
                        n[x][y][1] = 1;
                        n[x][y][2] = 1;
                    }
                }
                else if (angle[x][y] == 90 || angle[x][y] == angle[x][y] == -90){
                    //vertical comparison
                    if(binary[x][y][0] >= binary[x][y-1][0] && binary[x][y][0] >= binary[x][y+1][0]){
                        n[x][y][0] = 1;
                        n[x][y][1] = 1;
                        n[x][y][2] = 1;
                    }
                }
        }
    }
    myfile.open("image1.ppm"); //write to output.ppm
        myfile<<"P3 " << width << " " << height << " "<< "1\n";
        for (int i = 0; i < height; i++) {
            for (int j =0; j <  width; j++)
                for(int k=0; k<3;k++)
                    myfile<<n[j][i][k]<<' ';
            myfile<<"\n";
        }
        myfile.close();
     myfile.open("imagef.ppm"); //write to output.ppm
        myfile<<"P3 " << width << " " << height << " "<< "1\n";
        for (int i = 0; i < height; i++) {
            for (int j =0; j <  width; j++)
                for(int k=0; k<3;k++)
                    if(n[j][i][k]==h[j][i][k] && h[j][i][k]==1){
                        myfile<<n[j][i][k]<<' ';
                    }
                    else{
                        myfile << 0 << ' ';
                    }
            myfile<<"\n";
        }
        myfile.close();
    int ***edge = new int**[width];
    for(int i=0;i<width;i++){
        edge[i] = new int*[height];
        for(int j =0; j<height; j++){
            edge[i][j] = new int[3];
        }
    }
    for (int i = 0; i < height; i++) {
            for (int j =0; j <  width; j++)
                for(int k=0; k<3;k++)
                    if(n[j][i][k]==h[j][i][k] && h[j][i][k]==1){
                        edge[i][j][k] = 1;
                    }
                    else{
                       edge[i][j][k] = 0;
                    }
    }


}
int main(){
    part1();
    return 0;
}
