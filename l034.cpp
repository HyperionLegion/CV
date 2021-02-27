#include <iostream>
#include "stdio.h"
#include<ctime> 
#include <math.h>       /* pow */
#include <fstream>
#include <list> 
#include <iterator>
#include <iomanip>      // std::setprecision
#include <vector> 
#include <algorithm>    // std::sort
#include <chrono> 
#include <unordered_map>


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
        myfile.open("points.ppm"); //write to output.ppm
        myfile<<"P3  800  800  1\n";
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
            m[i][j][0]=1, m[i][j][1]=1, m[i][j][2]=1;//i = rows (up and down), j = columns (left and right)
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
        static void drawCircle(double x, double y, int colors[3]){ //draw circle of 2 with specified color at the x and y coordinate
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
        
};
class mapPoint{
    
    public:
    unsigned long long int x, y;
    mapPoint(unsigned long long int a, unsigned long long int b){
        x = a;
        y = b;
    }
    unsigned long long int getX(){
        return x;
    }
    unsigned long long int getY(){
        return y;
    }
    bool operator==(const mapPoint& p) const
    { 
        return x == p.x && y == p.y; 
    } 
};
class Distance{ //distance and 2 points
    double dist;
    Point p1, p2;
    public:
        Distance(){
            dist = 0;
        }
        Distance(double distance, Point one, Point two){
            dist = distance;
            p1 = one;
            p2 = two;
        }
        Distance(double distance){
            dist = distance;
        }
        double getDistance(){
            return dist;
        }
        Point getPoint1(){
            return p1;
        }
        Point getPoint2(){
            return p2;
        }
};
void draw(list<Point>& points, Point min1, Point min2){
    Point::clear();
    std::list<Point>::iterator it;
    int red[3] = {1,0,0};
    int black[3] = {0,0,0};

    std::ofstream out("points.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf());
    std::cout << std::fixed;
    for (it = points.begin();it!=points.end();it++){
        double x = it->getX();
        double y = it->getY();
        if((x==min1.getX()&&y==min1.getY())||(x==min2.getX()&&y==min2.getY())){
            Point::drawCircle(x, y, red);
        }
        else{
            Point::drawCircle(x, y, black);
        }
            cout << std::setprecision(23) << x << "  " << y << "\n";

    }
    std::cout.rdbuf(coutbuf); //reset to standard output again*/
    Point::draw();
}
Point p11, p12;
double time1;
void part1(){ //brute forcing
    list<Point> points;
    srand(time(0));
    Point min1;
    Point min2;
    for(int i=0;i<500000; i++){ // change number of points here
        Point point((double)rand()/RAND_MAX,(double)rand()/RAND_MAX);
        points.insert(points.begin(), point);
        if(i==0){
            min1 = point;
        }
        if(i==1){
            min2 = point;
        }
    }
   /* auto start = std::chrono::high_resolution_clock::now(); 
    std::list<Point>::iterator it;
    std::list<Point>::iterator it2;

    for (it = points.begin();it!=points.end();it++){
        for(it2=next(it,1); it2!=points.end(); it2++){
                Point point1 = *it;
                Point point2 = *it2;
                if(point1.distance(point2)<min1.distance(min2)){
                    min1 = point1;
                    min2 = point2;
                }
        }
    
        
    }
    auto stop = std::chrono::high_resolution_clock::now(); 
    p11 = min1;
    p12 = min2;
    time1 = duration_cast<microseconds>(stop - start).count();*/
    draw(points, min1, min2);
}
bool sorting(Point one, Point two){
    return one.getX()<two.getX();
}

Distance recur(vector<Point> &p, int start, int end){
    if(end - start+1==2){ //2 points
        Distance distance(p[start].distance(p[end]), p[start], p[end]);
        return distance;
    }
    else if(end - start+1==3){ //3 points
        double distance1 = p[start].distance(p[end]);
        double distance2 = p[start+1].distance(p[end]);
        double distance3 = p[start].distance(p[start+1]);
        if(distance1<=distance2 && distance1<=distance3){
            Distance distance(distance1, p[start], p[end]);
            return distance;
        }
        else if(distance2<=distance1 && distance2<=distance3){
            Distance distance(distance2, p[start+1], p[end]);
            return distance;
        }
        else{
            Distance distance(distance3, p[start], p[start+1]);
            return distance;
        }
    }
    else{
        Distance distance1 = recur(p, start, int((start+end)/2));
        Distance distance2 = recur(p, int((start+end)/2), end);
        Distance mindistance;
        if(distance1.getDistance()<=distance2.getDistance())
            mindistance = distance1;
        else{
            mindistance = distance2;
        }
         std::vector<Point>::iterator i;
        std::vector<Point>::iterator j;
        i = p.begin();
        j = p.begin();
        advance(i,int((start+end)/2.0)-1);
        advance(j,int((start+end)/2.0)+1);
        double dist = mindistance.getDistance();
        for(i; p[int((start+end)/2)].getX()-(*i).getX()<dist&&i!=p.begin(); i--){
                for(j; (*j).getX()-p[int((start+end)/2)].getX()<dist&&j!=p.end(); j++){
                    if((*i).distance(*j)<mindistance.getDistance()){
                    Distance distance((*i).distance(*j), *i, *j);
                    mindistance = distance;
                    }
                }
        }
        return mindistance;
    }
}
void output(Point a, Point b, Point c, Point d, double t1, double t2){
    std::ofstream out("results.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf());
    std::cout << std::fixed;

    cout << std::setprecision(26) << "Part 3: "<< "("<<a.getX()<<","<<a.getY()<<") , " << "("<<b.getX()<<","<<b.getY()<<")\nDistance: " <<a.distance(b)<<"\nTime: "<<std::setprecision(1)<<t1<<" microseconds\n";
    cout << std::setprecision(26) << "Part 4: "<< "("<<c.getX()<<","<<c.getY()<<") , " << "("<<d.getX()<<","<<d.getY()<<")\nDistance: " <<c.distance(d)<<"\nTime: "<<std::setprecision(1)<<t2<<" microseconds\n";
    std::cout.rdbuf(coutbuf); //reset to standard output again*/
}
void part2(){
    vector<Point> p;
    string line;
    ifstream myfile ("points.txt");
    while(getline(myfile,line)){
        Point point = Point(std::stod(line.substr(0,line.find(" "))), std::stod(line.substr(line.find(" ")+1)));
        p.push_back(point);
    }
    /*std::list<Point>::iterator it;
    for (it = points.begin();it!=points.end();it++){ //fill vector with points from part 1
        p.push_back(*it);
    }*/
    myfile.close();
    //merge sort: (time starts here)
    auto start = std::chrono::high_resolution_clock::now(); 
    sort(p.begin(), p.end(), sorting);
    Distance dist = recur(p, 0, p.size());
    auto stop = std::chrono::high_resolution_clock::now(); 
    //output(p11, p12, dist.getPoint1(), dist.getPoint2(), time1, duration_cast<microseconds>(stop - start).count());
    //cout << std::setprecision(26) << "Part 2: "<< "("<<dist.getPoint1().getX()<<","<<dist.getPoint1().getY()<<") , " << "("<<dist.getPoint2().getX()<<","<<dist.getPoint2().getY()<<")\nDistance: " <<dist.getPoint1().distance(dist.getPoint2())<<"\nTime: " << std::setprecision(1)<< duration_cast<microseconds>(stop - start).count() << " microseconds\n";
    p11 = dist.getPoint1();
    p12= dist.getPoint2();
    time1 = duration_cast<microseconds>(stop - start).count();
}
bool sorting2(Point one, Point two){
    return one.getY()<two.getY();
}
Distance mindistance = Distance(2);
Distance recur2(vector<Point> &p, int start, int end){
    if(end - start+1==2){ //2 points
        Distance distance(p[start].distance(p[end]), p[start], p[end]);
        return distance;
    }
    else if(end - start+1==3){ //3 points
        double distance1 = p[start].distance(p[end]);
        double distance2 = p[start+1].distance(p[end]);
        double distance3 = p[start].distance(p[start+1]);
        if(distance1<=distance2 && distance1<=distance3){
            Distance distance(distance1, p[start], p[end]);
            return distance;
        }
        else if(distance2<=distance1 && distance2<=distance3){
            Distance distance(distance2, p[start+1], p[end]);
            return distance;
        }
        else{
            Distance distance(distance3, p[start], p[start+1]);
            return distance;
        }
    }
    else{
        Distance distance1 = recur2(p, start, int((start+end)/2.0));
        Distance distance2 = recur2(p, int((start+end)/2.0), end);
        //Distance mindistance;
        if(distance1.getDistance()<=distance2.getDistance())
            if(distance1.getDistance()<mindistance.getDistance())
             mindistance = distance1;
        else{
            if(distance2.getDistance()<mindistance.getDistance())
            mindistance = distance2;
        }
         std::vector<Point>::iterator i;
        i = p.begin();
        vector<Point> vector2;
        advance(i,int((start+end)/2.0)-1);
        for(i; p[int((start+end)/2.0)].getX()-(*i).getX()<mindistance.getDistance()&&i!=p.begin(); i--){
            vector2.push_back(*i);
        }
        i = p.begin();
        advance(i,int((start+end)/2.0)+1);
        for(i; (*i).getX()-p[int((start+end)/2.0)].getX()<mindistance.getDistance()&&i!=p.end(); i++){
            vector2.push_back(*i);
        }
        sort(vector2.begin(), vector2.end(), sorting2);
        i = vector2.begin();
        for(i; i!=vector2.end();i++){
            std::vector<Point>::iterator j;
            j = vector2.begin();
            int count=0;
            for(j=next(i,1); j!=vector2.end()&&count<15; j++){
                 if((*i).distance(*j)<mindistance.getDistance()){
                    Distance distance((*i).distance(*j), *i, *j);
                    mindistance = distance;
                }
                count++;
            }
        }
        return mindistance;
    }
}
void part3(){
    mindistance = Distance(2);
   vector<Point> p;
    string line;
    ifstream myfile ("points.txt");
    while(getline(myfile,line)){
        Point point = Point(std::stod(line.substr(0,line.find(" "))), std::stod(line.substr(line.find(" ")+1)));
        p.push_back(point);
    }
    myfile.close();
    auto start = std::chrono::high_resolution_clock::now(); 
    sort(p.begin(), p.end(), sorting);
    Distance dist = recur2(p, 0, p.size());
    auto stop = std::chrono::high_resolution_clock::now(); 
    p11 = dist.getPoint1();
    p12 = dist.getPoint2();
    time1 = duration_cast<microseconds>(stop-start).count();
    //output(p11, p12, dist.getPoint1(), dist.getPoint2(), time1, duration_cast<microseconds>(stop - start).count());
    cout << std::setprecision(26) << "Part 3: "<< "("<<dist.getPoint1().getX()<<","<<dist.getPoint1().getY()<<") , " << "("<<dist.getPoint2().getX()<<","<<dist.getPoint2().getY()<<")\nDistance: " <<dist.getPoint1().distance(dist.getPoint2())<<"\nTime: " << std::setprecision(1)<<duration_cast<microseconds>(stop - start).count() << " microseconds\n";
}
mapPoint mapping(Point p, double size){
    mapPoint point((unsigned long long int)(p.getX()/size), (unsigned long long int)(p.getY()/size));
    return point;
}

class MyHashFunction { 
public: 
    size_t operator()(const mapPoint& p) const
    { 
        return (hash<int>()(p.x ^ (hash<int>()(p.y << 1)) >> 1)); 
    } 
}; 
void part4(){
    vector<Point> p;
    string line;
    ifstream myfile ("points.txt");
    while(getline(myfile,line)){
        Point point = Point(std::stod(line.substr(0,line.find(" "))), std::stod(line.substr(line.find(" ")+1)));
        p.push_back(point);
    }
    myfile.close();
    srand(time(0));
    auto start = std::chrono::high_resolution_clock::now();
     for(int x =0; x<p.size()-1; x++){//randomize points
         int y = int(rand()%int(p.size()-x))+x;
         iter_swap(p.begin()+x, p.begin()+y);
     }
 

    double size = (p[0].distance(p[1]))/2.0;
    unordered_map<mapPoint, Point, MyHashFunction> m;
    m.insert(pair<mapPoint, Point>(mapping(p[0], size), p[0]));
    m.insert(pair<mapPoint, Point>(mapping(p[1], size), p[1]));
    Distance mindistance(p[0].distance(p[1]), p[0], p[1]);
    for(int x=2; x<p.size();x++){ //map stuff
        mapPoint a = mapping(p[x], size);
        Distance min = Distance(2);
        for(int y=-2;y<3;y++){
            for(int z=-2;z<3;z++){
                if(m.count(mapPoint((unsigned long long int)(a.getX()+y), (unsigned long long int)(a.getY()+z)))){
                    if(min.getDistance()>p[x].distance(m.at(mapPoint((unsigned long long int)(a.getX()+y), (unsigned long long int)(a.getY()+z))))){
                        min = Distance(p[x].distance(m.at(mapPoint((unsigned long long int)(a.getX()+y), (unsigned long long int)(a.getY()+z)))),p[x], m.at(mapPoint((unsigned long long int)(a.getX()+y), (unsigned long long int)(a.getY()+z))));
                    }
                }
            }
        }
        if(mindistance.getDistance()>min.getDistance()){
                        mindistance = min;
                        size = mindistance.getDistance()/2.0;
                        //new map
                        unordered_map<mapPoint, Point, MyHashFunction> newMap;
                        for(int i =0; i<x; i++){
                            newMap.insert(pair<mapPoint, Point>(mapping(p[i], size), p[i]));
                        }
                        m = newMap;
        }
        m.insert(pair<mapPoint, Point>(mapping(p[x], size), p[x]));
    }
    auto stop = std::chrono::high_resolution_clock::now(); 
    output(p11, p12, mindistance.getPoint1(), mindistance.getPoint2(), time1, duration_cast<microseconds>(stop - start).count());
    cout << std::setprecision(26) << "Part 4: "<< "("<<mindistance.getPoint1().getX()<<","<<mindistance.getPoint1().getY()<<") , " << "("<<mindistance.getPoint2().getX()<<","<<mindistance.getPoint2().getY()<<")\nDistance: " <<mindistance.getPoint1().distance(mindistance.getPoint2())<<"\nTime: " << std::setprecision(1)<<duration_cast<microseconds>(stop - start).count() << " microseconds\n";
}
int main(){
    //part1();
    //part2();
    part3();
    part4();
    return 0;
}
