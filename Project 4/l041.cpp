#include <iostream>
#include "stdio.h"
#include<ctime> 
#include <math.h>       /* pow */
#include <fstream>
#include <iterator>
#include <iomanip>      // std::setprecision
#include <vector> 
#include <chrono> 


using namespace std;
using namespace std::chrono; 
static int m[800][800][3];
class Point{
    double x, y; //coordinates
    public:
        Point(){ //default constructor
            x = 0;
            y = 0;
        }
        static void draw(){
        ofstream myfile;
        myfile.open("clusters.ppm"); //write to output.ppm
        myfile<<"P3  800  800  255\n";
        for (int i = 0; i < 800; i++) {
            for (int j =0; j <  800; j++)
                for(int k=0; k<3;k++)
                    myfile<<m[i][j][k]<<' ';
            myfile<<"\n";
        }
        myfile.close();
        }
        Point(double x1, double y1){ //constructor with 2 args
            x = x1;
            y = y1;
        }
        static void clear(){ //reset and make image all white
        for (int i = 0; i < 800; i++) 
        for (int j = 0; j < 800; j++) {
            m[i][j][0]=255, m[i][j][1]=255, m[i][j][2]=255;//i = rows (up and down), j = columns (left and right)
        }
        }
        double getX(){
            return x;
        }
        double getY(){
            return y;
        }
        double distance(Point p){
            return sqrt(pow(p.getX()-x, 2)+pow(p.getY()-y,2));
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

void draw(vector<Point>& points, vector<int>& pointsCluster, vector<Point>& means){
    Point::clear();
    for(int x =0; x<points.size(); x++){
         int r, g, b;
         if(pointsCluster[x]==0){
             r=64, g=244, b=208;
         }
         else if(pointsCluster[x]==1){
             r=255, g=0, b=0;
         }
         else if(pointsCluster[x]==2){
             r=0, g=255, b=0;
         }
         else if(pointsCluster[x]==3){
             r=0,g=0,b=255;
         }
         else if(pointsCluster[x]==4){
             r=255,g=127,b=0;
         }
        int color[3] = {r, g, b};
        Point::drawCircle(points[x].getX(), points[x].getY(),color,2);
    }
    for(int x =0; x<means.size();x++){
        int color[3] = {0, 0, 0};
        Point::drawCircle(means[x].getX(), means[x].getY(), color,3);
    }
    Point::draw();
}
vector<int> recluster(vector<Point> points, vector<int> pointsCluster, vector<Point> means){
    for (int x =0; x<points.size(); x++){
        int cluster = 0;
        double mindist = points[x].distance(means[0]);
        for(int y =1; y<means.size(); y++){
            if(mindist>points[x].distance(means[y])){
                cluster = y;
                mindist = points[x].distance(means[y]);
            }
        }
        pointsCluster[x]=cluster;
    }
    return pointsCluster;
}
vector<Point> recalc(vector<Point> points, vector<int> pointsCluster, vector<Point> means){
    for(int i =0; i<means.size(); i++){ //i = cluster index
        double x =0, y=0;
        double count = 0;
        for(int j=0; j<points.size(); j++){
            if(pointsCluster[j]==i){
                x = x + points[j].getX();
                y = y + points[j].getY();
                count++;
            }
        }
        Point mean = Point(x/count, y/count);
        means[i] = mean;
    }
    return means;
}
void part1(){ //brute forcing
    const int k = 5;
    const int num = 100;
    vector<Point> points; //100 pts
    vector<int> pointsCluster; //100 pts, parallel to points value of which cluster
    //get 100 random points
    srand(time(0));
    for(int i=0;i<num; i++){ // change number of points here
        Point point((double)rand()/RAND_MAX,(double)rand()/RAND_MAX);
        points.insert(points.begin(), point);
    }
    for(int i=0; i<num; i++){
        pointsCluster.insert(pointsCluster.begin(), 0);
    }
    vector<Point> means; //size of number of clusters (5), value of the mean for the cluster 
    //fill with random means to start:
    for(int x =0; x<k; x++){
        Point point((double)rand()/RAND_MAX,(double)rand()/RAND_MAX);
        means.insert(means.begin(), point);
    }
    vector<vector<int>> colors; //size of # of clusters (5), just holds color (RGB in array of 3)  for the cluster
    //step 1 refinement in recluster and recalc methods
    //step 2 reach convergence check
    bool converge = false;
    while(!converge){
        vector<int> newCluster = recluster(points, pointsCluster, means);
        vector<Point> newmeans = recalc(points, newCluster, means);
        bool same = true;
        for(int x =0; x<newmeans.size(); x++){
            if(newmeans[x].getX()!=means[x].getX() || newmeans[x].getY()!=means[x].getY()){
                means = newmeans;
                pointsCluster = newCluster;
                same = false;
            }
        }
        if(same){
            converge = true;
            means = newmeans;
            pointsCluster = newCluster;
        }
    }
    draw(points, pointsCluster, means);
}

int main(){
    part1();
    return 0;
}
