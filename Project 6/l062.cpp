#include <iostream>
#include "stdio.h"
#include<ctime> 
#include <math.h>       /* pow */
#include <fstream>
#include <iterator>
#include <iomanip>      // std::setprecision
#include <vector> 
#include <chrono> 
#include <string>

using namespace std;
#define PI 3.14159265358979
int** votes;
int *** radius;
int *** circles;
int** edge;
void drawCircle(int xcint, int ycint, int colors[3], int radius, int width, int height){ //draw circle of 2 with specified color at the x and y coordinate
            //colors is an array of 3 ints to represent RGB for drawing
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
                    if(ycint+b<height&&xcint+a<width&&ycint+b>=0&&xcint+a>=0){
                    circles[ycint+b][xcint+a][0]=colors[0],circles[ycint+b][xcint+a][1]=colors[1],circles[ycint+b][xcint+a][2]=colors[2];
                    // cout << circles[ycint+b][xcint+a][0];
                    }
                    if(ycint-b>=0&&xcint+a<width&&ycint-b<height&&xcint+a>=0){
                    circles[ycint-b][xcint+a][0]=colors[0],circles[ycint-b][xcint+a][1]=colors[1],circles[ycint-b][xcint+a][2]=colors[2];
                    // cout <<  circles[ycint-b][xcint+a][0];
                    }
                    if(ycint+b<height&&xcint-a>=0&&ycint+b>=0&&xcint-a<width){
                    circles[ycint+b][xcint-a][0]=colors[0],circles[ycint+b][xcint-a][1]=colors[1],circles[ycint+b][xcint-a][2]=colors[2];
                    // cout << circles[ycint+b][xcint-a][0];
                    }
                    if(ycint-b>=0&&xcint-a>=0&&ycint-b<height&&xcint-a<width){
                    circles[ycint-b][xcint-a][0]=colors[0],circles[ycint-b][xcint-a][1]=colors[1],circles[ycint-b][xcint-a][2]=colors[2];
                    // cout << circles[ycint-b][xcint-a][0];
                    }
                    if(ycint+a<height&&xcint+b<width&&ycint+a>=0&&xcint+b>=0){
                    circles[ycint+a][xcint+b][0]=colors[0],circles[ycint+a][xcint+b][1]=colors[1],circles[ycint+a][xcint+b][2]=colors[2];
                    // cout << circles[ycint+a][xcint+b][0];
                    }
                    if(ycint-a>=0&&xcint+b<width&&ycint-a<height&&xcint+b>=0){
                    circles[ycint-a][xcint+b][0]=colors[0],circles[ycint-a][xcint+b][1]=colors[1],circles[ycint-a][xcint+b][2]=colors[2];
                    // cout << circles[ycint-a][xcint+b][0];
                    }
                    if(ycint+a<height&&xcint-b>=0&&ycint+a>=0&&xcint-b<width){
                    circles[ycint+a][xcint-b][0]=colors[0],circles[ycint+a][xcint-b][1]=colors[1],circles[ycint+a][xcint-b][2]=colors[2];
                    // cout << circles[ycint+a][xcint-b][0];
                    }
                    if(ycint-a>=0&&xcint-b>=0&&ycint-a<height&&xcint-b<width){
                    circles[ycint-a][xcint-b][0]=colors[0],circles[ycint-a][xcint-b][1]=colors[1],circles[ycint-a][xcint-b][2]=colors[2];
                    // cout << circles[ycint-a][xcint-b][0];
                    }
                
                b2_new -=(2*a)-3;
            }
        }
int circle(int xcint, int ycint, int radius, int width, int height){ //draw circle of 2 with specified color at the x and y coordinate
            //colors is an array of 3 ints to represent RGB for drawing
            int a, b, xmax, b2, b2_new, tb;
            int count = 0;
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
                   if(ycint+b<height&&xcint+a<width&&ycint+b>=0&&xcint+a>=0){
                       if(edge[ycint+b][xcint+a]==1){
                           count++;
                       }
                   }
                    if(ycint-b>=0&&xcint+a<width&&ycint-b<height&&xcint+a>=0){
                        if(edge[ycint-b][xcint+a]==1){
                            count++;
                        }
                    }
                    if(ycint+b<height&&xcint-a>=0&&ycint+b>=0&&xcint-a<width){
                        if(edge[ycint+b][xcint-a]==1){
                            count++;
                        }
                    }
                    if(ycint-b>=0&&xcint-a>=0&&ycint-b<height&&xcint-a<width){
                        if(edge[ycint-b][xcint-a]==1){
                            count++;
                        }
                    }
                    if(ycint+a<height&&xcint+b<width&&ycint+a>=0&&xcint+b>=0){
                        if(edge[ycint+a][xcint+b]==1){
                            count++;
                        }
                    }
                    if(ycint-a>=0&&xcint+b<width&&ycint-a<height&&xcint+b>=0){
                        if(edge[ycint-a][xcint+b]==1){
                            count++;
                        }
                    }
                    if(ycint+a<height&&xcint-b>=0&&ycint+a>=0&&xcint-b<width){
                        if(edge[ycint+a][xcint-b]==1){
                            count++;
                        }
                    }
                    if(ycint-a>=0&&xcint-b>=0&&ycint-a<height&&xcint-b<width){
                        if(edge[ycint-a][xcint-b]==1){
                            count++;
                        }
                    }
                
                b2_new -=(2*a)-3;
            }
            return count;
        }
void drawLine(int x, int y, int xs, int ys) {
    if (x == xs) {
        for (int b = std::min(y, ys); b <= std::max(y, ys); b++) {
            votes[b][x] = votes[b][x] + 1;
        }
    }
    else if (y == ys) {
        for (int b = std::min(x, xs); b <= std::max(x, xs); b++) {
            votes[y][b] = votes[y][b] + 1;
        }
    }
    else {
        if (abs(xs - x) >= abs(ys - y)) { //x is driving axis
            int xl, yl, xr, yr; //coords of left x and y, right x and y
            if (xs >= x) { //P1 is the left coord
                xl = x;
                yl = y;
                xr = xs;
                yr = ys;
            }
            else { //P2 is the left coord
                xl = xs;
                yl = ys;
                xr = x;
                yr = y;
            }
            int dx1 = xr - xl, dy1 = yr - yl;
            int e;
            if (dy1 > 0)
                e = dy1 - dx1;
            else
            {
                e = dy1 + dx1;
            }

            int j = yl;
            for (int i = xl; i <= xr; i++) {
                votes[j][i] = votes[j][i] + 1;
                if (dy1 >= 0) {
                    if (e >= 0) {
                        j += 1;
                        e -= dx1;
                    }
                }
                else {
                    if (e <= 0) {
                        j -= 1;
                        e += dx1;
                    }
                }
                e += dy1;
            }
        }
        else {//y is driving axis
            int xt, yt, xb, yb; //coords of bottom x and y, top x and y
            if (ys < y) { //P2 is the top coord
                xb = x;
                yb = y;
                xt = xs;
                yt = ys;
            }
            else { //P2 is the bottom coord
                xb = xs;
                yb = ys;
                xt = x;
                yt = y;
            }
            int dx1 = xt - xb, dy1 = yt - yb, i = xb;
            int e;
            if (dx1 >= 0)
                e = dx1 + dy1;
            else
            {
                e = -dy1 + dx1;
            }

            for (int j = yb; j >= yt; j--) {
                votes[j][i] = votes[j][i] + 1;
                if (dx1 >= 0) {
                    if (e >= 0) {
                        i += 1;
                        e += dy1;
                    }
                }
                else {
                    if (e <= 0) {
                        i -= 1;
                        e -= dy1;
                    }
                }
                e += dx1;
            }
        }
    }
}
void part1() {
    int r, g, b;
    ifstream infile("image.ppm");
    string line;
    getline(infile, line);
    getline(infile, line);

    const int width = std::stoi(line.substr(0, line.find(" ")), 0, 10);
    const int height = std::stoi(line.substr(line.find(" ") + 1), 0, 10);
    int*** original = new int** [width];
        for (int i = 0; i < width; i++) {
            original[i] = new int* [height];
            for (int j = 0; j < height; j++) {
                original[i][j] = new int[3];
                for(int x =0; x<3; x++){
                    original[i][j][x] =0;
                }
            }
    }
    int** grey = new int* [width];
    for (int i = 0; i < width; i++) {
        grey[i] = new int [height];
        for (int j = 0; j < height; j++) {
            grey[i][j] = 0;
        }
    }
    int** binary = new int* [width];
    for (int i = 0; i < width; i++) {
        binary[i] = new int [height];
        for (int j = 0; j < height; j++) {
            binary[i][j] = 0;
        }
    }
    double** angle = new double* [width];
    for (int i = 0; i < width; i++) {
        angle[i] = new double[height];
        for(int x =0; x<height; x++){
            angle[i][x]=0;
        }
    }
    double** angle2 = new double* [height];
    for (int i = 0; i < height; i++) {
        angle2[i] = new double[width];
        for(int x =0; x<width; x++){
            angle2[i][x]=0;
        }
    }
    getline(infile, line);
    int count = 0;
    while (getline(infile, line)) { //fill grey matrix
        while (line.length() > 1) {
            r = std::stoi(line.substr(0, line.find(" ")), 0, 10);
            line = line.substr(line.find(" ") + 1);
            g = std::stoi(line.substr(0, line.find(" ")), 0, 10);
            line = line.substr(line.find(" ") + 1);
            b = std::stoi(line.substr(0, line.find(" ")), 0, 10);
            line = line.substr(line.find(" ") + 1);
            original[count % (width)][count / width][0] = r;
            original[count % (width)][count / width][1] = g;
            original[count % (width)][count / width][2] = b;           
            grey[count % (width)][count / width] = (r + g + b) / 3;
            count++;
        }
    }
    ofstream myfile;
    myfile.open("imageg.ppm"); //write to output.ppm
    myfile << "P3 " << width << " " << height << " " << "255\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            for (int k = 0; k < 3; k++)
                myfile << grey[j][i] << ' ';
        myfile << "\n";
    }
    myfile.close();
    int derivY[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int derivX[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };
    for (int x = 1; x < width - 1; x++) {
        for (int y = 1; y < height - 1; y++) {
            int yvalue = 0;
            int xvalue = 0;
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    xvalue += grey[i + x][j + y] * derivX[i + 1][j + 1];
                    yvalue += grey[i + x][j + y] * derivY[i + 1][j + 1];
                }
            }
            binary[x][y] = sqrt(pow(xvalue, 2) + pow(yvalue, 2));
            angle[x][y] = atan2(yvalue, xvalue) * 180 / PI;
            angle2[y][x] = atan2(yvalue, xvalue);
        }
    }
    //hystheris
    int** h = new int* [width];
    for (int i = 0; i < width; i++) {
        h[i] = new int [height];
        for (int j = 0; j < height; j++) {
            h[i][j] =0;
        }
    }
    const int low = 150;
    const int high = 250;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (binary[x][y] >= high) {
                h[x][y]=2;
            }
            else if (binary[x][y] >= low && binary[x][y] < high) {
                h[x][y] = 1;
                h[x][y] = 1;
                h[x][y] = 1;
            }
            else {
                h[x][y] = 0;
                h[x][y] = 0;
                h[x][y]= 0;
            }
        }
    }
    //area fill

    bool done = false;
    bool** visited = new bool* [width];
    for (int i = 0; i < width; i++) {
        visited[i] = new bool[height];
        for(int x =0; x<height; x++){
            visited[i][x]=false;
        }
    }
    while (!done) {
        done = true;
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                if (h[x][y] == 2) {
                    if (!visited[x][y]) {
                        visited[x][y] = true;
                        if (x + 1 < width) {
                            if (h[x + 1][y] == 1) {
                                h[x + 1][y] = 2;

                                done = false;
                            }
                            if (y + 1 < height) {
                                if (h[x + 1][y + 1] == 1) {
                                    h[x + 1][y + 1] = 2;
                                    done = false;
                                }
                            }
                            if (y - 1 >= 0) {
                                if (h[x + 1][y - 1] == 1) {
                                    h[x + 1][y - 1] = 2;
                                    done = false;
                                }
                            }
                        }
                        if (x - 1 >= 0) {
                            if (h[x - 1][y] == 1) {
                                h[x - 1][y] = 2;
                                done = false;
                            }
                            if (y + 1 < height) {
                                if (h[x - 1][y + 1] == 1) {
                                    h[x - 1][y + 1] = 2;
                                    done = false;
                                }
                            }
                            if (y - 1 >= 0) {
                                if (h[x - 1][y - 1] == 1) {
                                    h[x - 1][y - 1] = 2;
                                    done = false;
                                }
                            }
                        }
                        if (y + 1 < height) {
                            if (h[x][y + 1] == 1) {
                                h[x][y + 1] = 2;
                                done = false;
                            }
                        }
                        if (y - 1 >= 0) {
                            if (h[x][y - 1] == 1) {
                                h[x][y - 1] = 2;
                                done = false;
                            }
                        }
                    }
                }
            }
        }
    }
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (h[x][y] == 2) {
                h[x][y] = 1;
            }
            else {
                h[x][y] = 0;
            }
        }
    }
    myfile.open("image2.ppm"); //write to output.ppm
    myfile << "P3 " << width << " " << height << " " << "1\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            for (int k = 0; k < 3; k++)
                myfile << h[j][i] << ' ';
        myfile << "\n";
    }
    myfile.close();

    //nonmax supression
    int** n = new int* [width];
    for (int i = 0; i < width; i++) {
        n[i] = new int [height];
        for (int j = 0; j < height; j++) {
            n[i][j] = 0;
        }
    }
    for (int x = 1; x < width - 1; x++) { //what to do about the very edges of the image for angles and then how does the algo work? straight lines ie
        for (int y = 1; y < height - 1; y++) {
            if (angle[x][y] >= 0)
                angle[x][y] = int(angle[x][y] + (22.5)) / 45 * 45;
            else
                angle[x][y] = int(angle[x][y] - (22.5)) / 45 * 45;
            if (angle[x][y] == 0 || angle[x][y] == 180 || angle[x][y] == -0 || angle[x][y] == -180) {
                if (binary[x][y] >= binary[x - 1][y] && binary[x][y] >= binary[x + 1][y]) {
                    n[x][y]=1;
                }
            }
            else if (angle[x][y] == 45 || angle[x][y] == -135) {
                //diagnol comparison up right
                if (binary[x][y] >= binary[x + 1][y + 1] && binary[x][y] >= binary[x - 1][y - 1]) {
                    n[x][y] =1;
                }
            }
            else if (angle[x][y] == 135 || angle[x][y] == -45) {
                //diagnol comparison up left
                if (binary[x][y] >= binary[x - 1][y + 1] && binary[x][y] >= binary[x + 1][y - 1]) {
                    n[x][y]=1;
                }
            }
            else if (angle[x][y] == 90 || angle[x][y] == angle[x][y] == -90) {
                //vertical comparison
                if (binary[x][y] >= binary[x][y - 1] && binary[x][y] >= binary[x][y + 1]) {
                    n[x][y]=1;
                }
            }
        }
    }
    myfile.open("image1.ppm"); //write to output.ppm
    myfile << "P3 " << width << " " << height << " " << "1\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            for (int k = 0; k < 3; k++)
                myfile << n[j][i] << ' ';
        myfile << "\n";
    }
    myfile.close();
    myfile.open("imagef.ppm"); //write to output.ppm
    myfile << "P3 " << width << " " << height << " " << "1\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 3; k++) {
                if (n[j][i] == h[j][i] && h[j][i] == 1) {
                    myfile << n[j][i] << ' ';
                }
                else {
                    myfile << 0 << ' ';
                }
            }
            myfile << "\n";
        }
    }
    myfile.close();
    edge = new int* [width];
    for (int i = 0; i < width; i++) {
        edge[i] = new int [height];
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            for (int k = 0; k < 3; k++)
                if (n[j][i] == h[j][i] && h[j][i] == 1) {
                    edge[j][i] = 1;
                }
                else {
                    edge[j][i] = 0;
                }
    }
    votes = new int* [height];
    for (int i = 0; i < height; i++) {
        votes[i] = new int[width];
    }
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            votes[x][y] = 0;
        }
    }    for (int i = 1; i < width - 1; i++) {
        for (int j = 1; j < height - 1; j++) {
            if (edge[i][j] == 1) {
                int startx, starty, endx, endy;
                if (angle2[j][i] == 0 || angle2[j][i] == 180) {
                    startx = 0;
                    endx = width - 1;
                    starty = j;
                    endy = j;
                }
                else if (angle2[j][i] == 90 || angle2[j][i] == -90) {
                    starty = 0;
                    endy = height - 1;
                    startx = i;
                    endx = i;

                }
                else {
                    double slope = tan(angle2[j][i]);
                    if (slope * -1 * i + j >= height) {
                        starty = height - 1;
                        startx = (starty - j) / slope + i;
                    }
                    else if (slope * -1 * i + j < 0) {
                        starty = 0;
                        startx = (starty - j) / slope + i;
                    }
                    else {
                        startx = 0;
                        starty = slope * -1 * i + j;
                    }
                    if (slope * (width - 1 - i) + j >= height) {
                        endy = height - 1;
                        endx = (endy - j) / slope + i;
                    }
                    else if (slope * (width - 1 - i) + j < 0) {
                        endy = 0;
                        endx = (endy - j) / slope + i;
                    }
                    else {
                        endx = width - 1;
                        endy = slope * (endx - i) + j;
                    }
                    drawLine(startx, starty, endx, endy);
                }
                //y-j = m(x-i)
            }
        }
    }
    int max = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (votes[i][j] > max)
                max = votes[i][j];
        }
    }
    myfile.open("imagev.ppm"); //write to output.ppm
    //if(max<255){
    myfile << "P3 " << width << " " << height << " " << max<< "\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 3; k++)
                myfile << (votes[i][j]) << ' ';
        }
        myfile << "\n";
    }
    myfile.close();
    circles = new int** [height];
    for (int i = 0; i < height; i++) {
        circles[i] = new int* [width];
        for (int j = 0; j < width; j++) {
            circles[i][j] = new int[3];
            for(int x =0; x<3; x++){
                circles[i][j][x]=0;
            }
        }
    }
    int red[3] = {255, 0, 0};
    for(int i=0; i<height; i++){
        for(int j=0; j<width;j++){
            if(votes[i][j]>=0.7*max){
                for(int x= 0; x<6; x++)
                    drawCircle(j, i, red, x, width, height);
            }
        }
    }
    myfile.open("imageCC.ppm"); //write to output.ppm
    myfile << "P3 " << width << " " << height << " " << 255<< "\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if(circles[i][j][0]==255&&circles[i][j][1]==0&&circles[i][j][2]==0){
                    myfile << "255 0 0 ";
            }
            else{
                myfile << original[j][i][0] << ' '<< original[j][i][1] << ' ' << original[j][i][2] << ' ';
            }
        }
        myfile << "\n";
    }
    myfile.close();
    radius = new int** [height];
    for (int i = 0; i < height; i++) {
        radius[i] = new int* [width];
        for (int j = 0; j < width; j++) {
            radius[i][j] = new int[0];
        }
    }
    for (int i = 0; i < height; i++) {
        circles[i] = new int* [width];
        for (int j = 0; j < width; j++) {
            circles[i][j] = new int[3];
            for(int x =0; x<3; x++){
                circles[i][j][x]=0;
            }
        }
    }
    //cout << "new\n";
    const int maxr = 500; //change this later
    const int radiusthreshold = 80;
    //delete red;
    //red[3] = {255, 0, 0};
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if(votes[i][j]>=0.7*max){
                bool arr[maxr] = {false};
                int count =0;
                for(int r = 1; r<=maxr; r++){
                    if (circle(i, j, r, width, height) > radiusthreshold){
                        arr[r] = true;
                        count++;
                    }
                }
                int* radiuses = new int[count];
                count = 0;
                for(int x =0; x< maxr; x++){
                    if(arr[x]){
                        radiuses[count] = x;
                        count++;
                    }
                }
                radius[i][j] = radiuses;
                for(int x=0;x<sizeof(radiuses);x++)
                    drawCircle(j, i, red, radiuses[x], width, height);
            }
        }
    }
    //cout << red[0] << " " << red[1] << " " <<red[2] << " ";
    myfile.open("imagecircles.ppm"); //write to output.ppm
    myfile << "P3 " << width << " " << height << " " << 255<< "\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if(circles[i][j][0]==255&&circles[i][j][1]==0&&circles[i][j][2]==0){
                    myfile << "255 0 0 ";
            }
            else{
                myfile << original[j][i][0] << ' '<< original[j][i][1] << ' ' << original[j][i][2] << ' ';
            }
        }
        myfile << "\n";
    }
    myfile.close();

    //for each center, look at the correct radiuses and determine from size and color what kind of coin it is
    //use percentages

    //additions

}
int main() {
    part1();
    return 0;
}
