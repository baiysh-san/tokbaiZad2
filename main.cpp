#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
Mat image1024;

void openCVMethod(){
    Mat image512;
    Mat image256;
    Mat image128;
    Mat image64;
    Mat image32;
    if(image1024.cols==1024 and image1024.rows==1024){
        cv::resize(image1024, image512, cv::Size(), 0.5, 0.5);
    }
    cv::resize(image512, image256, cv::Size(), 0.5, 0.5);
    cv::resize(image256, image128, cv::Size(), 0.5, 0.5);
    cv::resize(image128, image64, cv::Size(), 0.5, 0.5);
    cv::resize(image64, image32, cv::Size(), 0.5, 0.5);
    imshow("1024x1024",image1024);
    imshow("512x512resize", image512);
    imshow("256x256resize", image256);
    imshow("128x128resize", image128);
    imshow("64x64resize", image64);
    imshow("32x32resize", image32);
    cv::resize(image32, image64, cv::Size(), 2, 2);
    cv::resize(image64, image128, cv::Size(), 2, 2);
    cv::resize(image128, image256, cv::Size(), 2, 2);
    cv::resize(image256, image512, cv::Size(), 2, 2);
    cv::resize(image512, image1024, cv::Size(), 2, 2);
    imshow("8 bit v2",image1024);
    imshow("512 v2", image512);
    imshow("256 v2", image256);
    imshow("128 v2", image128);
    imshow("64 v2", image64);
    imshow("32 v2", image32);
}

Mat toIncrease(Mat image){ // увеличить
    int cols = image.cols*2;
    int rows = image.rows*2;
    Mat out(rows, cols, CV_8UC1, Scalar(0));
    for (int y = 0; y < rows; y++){
        for (int x = 0; x < cols; x++){
            out.at<uchar>(y,x)=image.at<uchar>(y/2,x/2);
        }
    }
    return out;
}
Mat toDecrease(Mat image){ //уменшить
    int cols = image.cols;
    int rows = image.rows;
    Mat out(rows/2, cols/2, CV_8UC1, Scalar(0));
    for (int y = 0; y < rows; y++){
        for (int x = 0; x < cols; x++){
            if(y%2==0&&x%2==0){
                out.at<uchar>(y/2,x/2)=image.at<uchar>(y,x);
            }
        }
    }
    return out;
}
void myMethod(){
    Mat im1024 = image1024.clone();
    Mat im512 = toDecrease(im1024);
    Mat im256 = toDecrease(im512);
    Mat im128 = toDecrease(im256);
    Mat im64 = toDecrease(im128);
    Mat im32 = toDecrease(im64);
    imshow("1024x1024", im1024);
    imshow("512x512decrease", im512);
    imshow("256x256decrease", im256);
    imshow("128x128decrease", im128);
    imshow("64x64decrease", im64);
    imshow("32x32decrease", im32);
    im64 = toIncrease(im32);
    im128 = toIncrease(im64);
    im256 = toIncrease(im128);
    im512 = toIncrease(im256);
    im1024 = toIncrease(im512);
    imshow("64x64increase", im64);
    imshow("128x128increase", im128);
    imshow("256x256increase", im256);
    imshow("512x512increase", im512);
    imshow("1024x1024increase", im1024);
}

int main(int argc) {
    image1024 = imread("/home/baiysh/ClionProjects/tokbaiZad2/margot-robbie-1024.jpg", CV_8U);
    if(!image1024.data){
        return -1;
    }
    //openCVMethod(); выбираем метод
    myMethod();
    waitKey(0);
    return 0;
}