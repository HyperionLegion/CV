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
class Point{ //point and node class
    vector<double> features; //coordinates
    vector<double> borders;
    Point *left;
    Point *right;
    int index;
    public:
        Point(){ //default constructor
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
        Point(vector<double> f, int i){ //constructor with 2 args
            features = f;
            left =NULL;
            right=NULL;
            index = i;
            for(int y=0;y<features.size();y++){
                borders.push_back(0);
                borders.push_back(1);
            }
        }
        static void clear(){ //reset and make image all white
        for (int i = 0; i < 800; i++) 
        for (int j = 0; j < 800; j++) {
            m[i][j][0]=255, m[i][j][1]=255, m[i][j][2]=255;//i = rows (up and down), j = columns (left and right)
        }
        }
        int getIndex(){
            return index;
        }
        void setBorders(vector<double> b){
            borders = b;
        }
        vector<double> getBorders(){
            return borders;
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

void part31(int num, int numfeatures){
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
double calc(double x, double y, Point p1, Point p2){
    double x1 = p1.getFeatures()[0];
    double y1= p1.getFeatures()[1];
    double x2 = p2.getFeatures()[0];
    double y2 = p2.getFeatures()[1];
    if(x1-x2==0){
        return (y-((y1+y2)/2.0));
    }
    else if(y1-y2==0){
        return (x-((x1+x2)/2.0));
    }
    else{
        double slope = -1*(x1-x2)/(y1-y2);
        return (y - ((y1+y2)/2+(x-(x1+x2)/2)*(slope)));
    }
}

void update(Point &p, vector<Point> &possibles, vector<int> &pointsCluster){
    if(&(p)!=0){
    vector<Point> realPossibles;
    vector<int> remove;
    for(int x =0; x<possibles.size();x++){
        remove.push_back(0);
    }
    vector<double> borders = p.getBorders();
    if(possibles.size()>1){
    for(int x =0; x<possibles.size(); x++){
        for(int y=x+1;y<possibles.size();y++){
            if(calc(possibles[y].getFeatures()[0], possibles[y].getFeatures()[1],possibles[x],possibles[y])>0&&calc(borders[0], borders[2],possibles[x],possibles[y])<0&&calc(borders[1], borders[2],possibles[x],possibles[y])<0&&calc(borders[0], borders[3],possibles[x],possibles[y])<0&&calc(borders[1], borders[3],possibles[x],possibles[y])<0){
                remove[y]=1;
            }
            if(calc(possibles[y].getFeatures()[0], possibles[y].getFeatures()[1],possibles[x],possibles[y])<0&&calc(borders[0], borders[2],possibles[x],possibles[y])>0&&calc(borders[1], borders[2],possibles[x],possibles[y])>0&&calc(borders[0], borders[3],possibles[x],possibles[y])>0&&calc(borders[1], borders[3],possibles[x],possibles[y])>0){
                remove[y]=1;
            }
            if(calc(possibles[x].getFeatures()[0], possibles[x].getFeatures()[1],possibles[x],possibles[y])<0&&calc(borders[0], borders[2],possibles[x],possibles[y])>0&&calc(borders[1], borders[2],possibles[x],possibles[y])>0&&calc(borders[0], borders[3],possibles[x],possibles[y])>0&&calc(borders[1], borders[3],possibles[x],possibles[y])>0){
                remove[x]=1;
            }
            if(calc(possibles[x].getFeatures()[0], possibles[x].getFeatures()[1],possibles[x],possibles[y])>0&&calc(borders[0], borders[2],possibles[x],possibles[y])<0&&calc(borders[1], borders[2],possibles[x],possibles[y])<0&&calc(borders[0], borders[3],possibles[x],possibles[y])<0&&calc(borders[1], borders[3],possibles[x],possibles[y])<0){
                remove[x]=1;
            }
        }
    }
    }
     for(int x =0; x<possibles.size();x++){
         if(remove[x]==0)
            realPossibles.push_back(possibles[x]);
    }
    //realPossibles = possibles;
    //eliminate if the other one dominates
    //nested for loop to eliminate not possible
    //find real cluster out of possibles into real possibles
    double mindist = p.distance(realPossibles[0]);
    int cluster=realPossibles[0].getIndex();
     for(int y =0; y<realPossibles.size(); y++){
            if(mindist>p.distance(realPossibles[y])){
                cluster = realPossibles[y].getIndex();
                mindist = p.distance(realPossibles[y]);
            }
        }
    pointsCluster[p.getIndex()]=cluster;
    //update pointsCluster at p.getIndex();
    update(*(p.getRight()), realPossibles, pointsCluster);
    update(*(p.getLeft()), realPossibles, pointsCluster);
    //pass possible to children
    }
}
vector<int> recluster(vector<Point> &points, vector<int> &pointsCluster, vector<Point> &means){
     update(points[0], means, pointsCluster); //traverse
     return pointsCluster;
}
vector<Point> recalc(vector<Point> points, vector<int> pointsCluster, vector<Point> means){
    for(int i =0; i<means.size(); i++){ //i = cluster index
        double x =0, y=0;
        int count = 0;
        for(int j=0; j<points.size(); j++){
            if(pointsCluster[j]==i){
                x = x + points[j].getFeatures()[0];
                y = y + points[j].getFeatures()[1];
                count++;
            }
        }
        vector<double> f;
        f.push_back(x/count);
        f.push_back(y/count);
        Point mean = Point(f, i);
        means[i] = mean;
    }
    return means;
}
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
        Point::drawCircle(points[x].getFeatures()[0], points[x].getFeatures()[1],color,2);
    }
    for(int x =0; x<means.size();x++){
        int color[3] = {0, 0, 0};
        Point::drawCircle(means[x].getFeatures()[0], means[x].getFeatures()[1], color,3);
    }
    Point::draw();
}
void part4(){
    //call part 3 to build tree
    int k = 5;
    int num = 50;
    int numfeatures=2;
    Point::clear();
    std::string s = "";
    cout << "Do you want to generate points? Type Y or N: ";
    cin >> s;
    if(!s.compare("Y")){
        part31(num, numfeatures);
    }
    vector<Point> p;
    string line;
    ifstream myfile ("points.txt");
    int index =0;
    while(getline(myfile,line)){
        vector<double> f;
        for(int x=0;x<numfeatures;x++){
            f.push_back(std::stod(line.substr(0,line.find(" "))));
            line = line.substr(line.find(" ")+2);
        }
        Point point = Point(f, index);
        index++;
        p.push_back(point);
    }
    num = p.size();
    myfile.close();
     
    Point *curr = &p[0];
    vector<double> original;
    for(int y=0;y<numfeatures;y++){
                original.push_back(0);
                original.push_back(1);
    }
    p[0].setBorders(original);
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
               double f1 = p[x].getFeatures()[index];
               double f2 = (*curr).getFeatures()[index];
               Point *next;
               if(f1<f2){
                   borders[2*index+1]=f2;
                   if(&*((*curr).getLeft())==0){
                        (*curr).setLeft(p[x]);
                        p[x].setBorders(borders);
                        empty=true;
                   }
                   else{
                   next = ((*curr).getLeft()); //next node to look at is the value (node) at the left child
                   }
               }
               else{
                   borders[2*index]=f2;
                   if(&*((*curr).getRight())==0){
                        (*curr).setRight(p[x]);
                        p[x].setBorders(borders);
                       empty=true;
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
         }
     }
    vector<int> pointsCluster; //100 pts, parallel to points value of which cluster
    //get 100 random points
    
    for(int i=0; i<num; i++){
        pointsCluster.insert(pointsCluster.begin(), 0);
    }
    vector<Point> means; //size of number of clusters (5), value of the mean for the cluster 
    //fill with random means to start:
    for(int x =0; x<k; x++){
        vector<double> random;
        for(int y=0;y<numfeatures;y++){
                random.push_back((double)rand()/RAND_MAX);
        }
        Point point(random, x);
        means.push_back(point);
    }
    //step 1 refinement in recluster and recalc methods
    //step 2 reach convergence check
    bool converge = false;
    while(!converge){
        vector<int> newCluster = recluster(p, pointsCluster, means);
        vector<Point> newmeans = recalc(p, newCluster, means);
        bool same = true;
        for(int x =0; x<newmeans.size(); x++){
            if(newmeans[x].getFeatures()[0]!=means[x].getFeatures()[0] || newmeans[x].getFeatures()[1]!=means[x].getFeatures()[1]){
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
    draw(p, pointsCluster, means);
    //then use kmeans (only need to calc distances for possible centroids with the boundaries of the node closer to another centroid)
}
int main(){
    part4();
    return 0;
}
