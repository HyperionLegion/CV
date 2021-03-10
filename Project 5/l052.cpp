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
        myfile.open("imagem.ppm"); //write to output.ppm
        myfile<<"P3 " << width << " " << height << " "<< "1\n";
        for (int i = 0; i < height; i++) {
            for (int j =0; j <  width; j++)
                for(int k=0; k<3;k++)
                    myfile<<binary[j][i][k]<<' ';
            myfile<<"\n";
        }
        myfile.close();

    //derivatives for G(X)
    //magnitude of G(X) and choose threshold

}
void part2(){
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
    const int low = 150;
    const int high = 250;
    const int threshold = 200;
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
                if(binary[x][y][0]>=threshold){ //do you need to compute hystheris only on values that are above a threshold?
                angle[x][y] = int((int(angle[x][y]+(45/2))))/45 * 45;
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

}
int main(){
    part2();
    return 0;
}
