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
const int width = 960;
const int height = 960;
int grey[width][height][3];
int binary[width][height][3];
void drawGrey(){
        ofstream myfile;
        myfile.open("grey.ppm"); //write to output.ppm
        myfile<<"P3 "<<  width << " " << height << " "<< "255\n";
        for (int i = 0; i < height; i++) {
            for (int j =0; j <  width; j++)
                for(int k=0; k<3;k++)
                    myfile<<grey[j][i][k]<<' ';
            myfile<<"\n";
        }
        myfile.close();
}
void drawBinary(){
        ofstream myfile;
        myfile.open("binary.ppm"); //write to output.ppm
        myfile<<"P3 " << width << " " << height << " "<< "1\n";
        for (int i = 0; i < height; i++) {
            for (int j =0; j <  width; j++)
                for(int k=0; k<3;k++)
                    myfile<<binary[j][i][k]<<' ';
            myfile<<"\n";
        }
        myfile.close();
}
void part1(){

    int r,g, b;
    ifstream infile("input.ppm");
    string line;
    getline(infile, line);
    getline(infile, line);
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
    drawGrey();
    int derivX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int derivY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
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
    const int threshold = 180;
    for(int x=0; x<width; x++){
        for(int y=0; y<height; y++){
            if(binary[x][y][0]>threshold){
                binary[x][y][0] = 1;
                binary[x][y][1] = 1;
                binary[x][y][2] = 1;
            }
            else{
                binary[x][y][0] = 0;
                binary[x][y][1] = 0;
                binary[x][y][2] = 0;
            }
        }
    }
    drawBinary();

    //derivatives for G(X)
    //magnitude of G(X) and choose threshold

}
int main(){
    part1();
    return 0;
}
