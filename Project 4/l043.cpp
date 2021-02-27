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
static int m[800][800][3];
class Point{
    vector<double> features; //coordinates
    Point *left;
    Point *right;
    public:
        Point(){ //default constructor
        }
        static void draw(){
        ofstream myfile;
        myfile.open("diagram.ppm"); //write to output.ppm
        myfile<<"P3  800  800  1\n";
        for (int i = 0; i < 800; i++) {
            for (int j =0; j <  800; j++)
                for(int k=0; k<3;k++)
                    myfile<<m[i][j][k]<<' ';
            myfile<<"\n";
        }
        myfile.close();
        }
        Point(vector<double> f){ //constructor with 2 args
            features = f;
            left =NULL;
            right=NULL;
        }
        static void clear(){ //reset and make image all white
        for (int i = 0; i < 800; i++) 
        for (int j = 0; j < 800; j++) {
            m[i][j][0]=1, m[i][j][1]=1, m[i][j][2]=1;//i = rows (up and down), j = columns (left and right)
        }
        }

        void setLeft(Point& p){
            left = &p;
        }
        void setRight(Point& p){
            right=&p;
        }
        Point * getLeft(){
            return left;
        }
        Point * getRight(){
            return right;
        }
        vector<double> getFeatures(){
            return features;
        }
        double distance(Point p){
            double sum = 0;
            for(int x =0; x<features.size(); x++){
                sum = sum + pow(p.getFeatures()[x]-features[x], 2);
            }
            return sqrt(sum);
        }
        static void drawLine(int x, int y, int xs, int ys, int colors[3]){
if(x==xs){
    for(int b =std::min(y, ys); b<=std::max(y,ys); b++){
        m[b][x][0]=colors[0],m[b][x][1]=colors[1],m[b][x][2]=colors[2];
    }
}
else if(y==ys){
    for(int b =std::min(x, xs); b<=std::max(x,xs); b++){
        m[y][b][0]=colors[0],m[y][b][1]=colors[1],m[y][b][2]=colors[2];
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
             m[j][i][0] = colors[0], m[j][i][1] =colors[1],m[j][i][2] =colors[2];
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
             m[j][i][0] = colors[0], m[j][i][1] = colors[1],m[j][i][2] = colors[2];
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
        static void drawCircle(double x, double y, int colors[3], int radius){ //draw circle of radius with specified color at the x and y coordinate
            //colors is an array of 3 ints to represent RGB for drawing
            int xcint = int(800.0*x+0.5);
            int ycint = int(800.0*y+0.5);
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
        
};
const int num = 10;
const int numfeatures = 2;
void part31(){
    srand(time(0));
    std::ofstream out("points.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf());
    std::cout << std::fixed;
    for(int x =0; x<num;x++){
        vector<double> coords;
        for(int y=0;y<numfeatures;y++)
            cout << std::setprecision(23) << (double)rand()/RAND_MAX << "  ";
        cout << "\n";
    }
    std::cout.rdbuf(coutbuf); //reset to standard output again*/
}
void part3(){
    Point::clear();
    std::string s = "";
    cout << "Do you want to generate points? Type Y or N: ";
    cin >> s;
    if(!s.compare("Y")){
        part31();
    }
    vector<Point> p;
    string line;
    ifstream myfile ("points.txt");
    while(getline(myfile,line)){
        vector<double> f;
        for(int x=0;x<numfeatures;x++){
            f.push_back(std::stod(line.substr(0,line.find(" "))));
            line = line.substr(line.find(" ")+2);
        }
        Point point = Point(f);
        p.push_back(point);
    }
    myfile.close();
     
     //drawline for first point
    // Point *curr = &p[0];
    // (*curr).setLeft(p[1]);
    // cout << (*((*curr).getLeft())).getFeatures()[0];
    // Point *next = (*curr).getLeft();
    // cout << (*next).getFeatures()[0];
    // curr = next;
    // cout << "\n";
    // cout << (*curr).getFeatures()[0];
    // cout << "\n";
    // cout << p[0].getFeatures()[0];
      int colors[3] = {1, 0, 0};
      Point::drawLine(int(799.0*p[0].getFeatures()[0]),0,int(799.0*p[0].getFeatures()[0]),799, colors);
      int black[3] = {0,0,0};
      Point::drawCircle(p[0].getFeatures()[0], p[0].getFeatures()[1], black, 3);
      Point *curr = &p[0];
    //   cout << (*curr).getFeatures()[1];
    //   (*curr).setLeft(p[1]);
    //   Point *next = (*curr).getLeft();
    //   curr = next;
    //   cout << (*curr).getFeatures()[1];
    //   (*curr).setRight(p[2]);
    //   next = (*curr).getRight();
    //   curr = next;
    //         cout << (*curr).getFeatures()[1];
     for(int x =1;x<p.size();x++){
        int index = 0;
         Point *curr = &p[0];
         bool empty = false;
         vector<double> borders;
               for(int y=0;y<numfeatures;y++){
                borders.push_back(0);
                borders.push_back(1);
               }
         while(!empty){ //while havent found empty spot
               
    
    //         //update boolean according to direction taken so you know which child to use later
    //         //compare current point with new point at the index feature
               double f1 = p[x].getFeatures()[index];
               double f2 = (*curr).getFeatures()[index];
               Point *next;
               if(f1<f2){
                   borders[2*index+1]=f2;
                   if(&*((*curr).getLeft())==0){
                        (*curr).setLeft(p[x]);
                        if(index%2==0){
                            int colors[3] = {0,0,1};
                           Point::drawLine(int(799.0*borders[0]), int(799.0*p[x].getFeatures()[1]), int(799.0*borders[1]), int(799.0*p[x].getFeatures()[1]), colors);
                        }else{
                            int colors[3] = {1,0,0};
                           Point::drawLine(int(799.0*p[x].getFeatures()[0]), int(799.0*borders[2]), int(799.0*p[x].getFeatures()[0]), int(799.0*borders[3]), colors);
                        }
                        empty=true;
                        int colors[3] = {0, 0, 0};
                        Point::drawCircle(p[x].getFeatures()[0], p[x].getFeatures()[1], colors, 3);
                   }
                   else{
                   next = ((*curr).getLeft()); //next node to look at is the value (node) at the left child
                   }
               }
               else{
                   borders[2*index]=f2;
                   if(&*((*curr).getRight())==0){
                        (*curr).setRight(p[x]);
                      if(index%2==0){
                          int colors[3] = {0,0,1};
                           Point::drawLine(int(799.0*borders[0]), int(799.0*p[x].getFeatures()[1]), int(799.0*borders[1]), int(799.0*p[x].getFeatures()[1]), colors);
                      }
                       else{
                           int colors[3] = {1,0,0};
                           Point::drawLine(int(799.0*p[x].getFeatures()[0]), int(799.0*borders[2]), int(799.0*p[x].getFeatures()[0]), int(799.0*borders[3]), colors);
                       }
                       empty=true;
                        int colors[3] = {0, 0, 0};
                        Point::drawCircle(p[x].getFeatures()[0], p[x].getFeatures()[1], colors, 3);
                   }
                   else{
                   next = (*curr).getRight();
                   }
               }
               if(!empty){
               index++;
               curr = next;
               if(index==numfeatures)
                    index =0;
               }
               
    //         //if less, make left the curr
    //         //else make right the curr
    //         //at the end of each case make prev = curr
    //         //in either case increase the index and reset index back to 0 if == numfeatures
         }

    //     //set curr to the new point and update the tree with prev pointing to the new point left/right depending on the prev (pointer child of previous node should be filled)
    //     //draw the line
     }
    //  Point *point = &p[0];
    //  cout << (*((*((*point).getLeft())).getRight())).getFeatures()[0];
     Point::draw();
}
int main(){
    //part1();
    //part2();
    //part31();
    part3();
    return 0;
}
