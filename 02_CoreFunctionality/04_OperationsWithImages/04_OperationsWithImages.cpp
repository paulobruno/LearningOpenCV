#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>


int main(int argc, char* argv[])
{
    // Input/Output
    cv::String filename = "HappyFish.png";
    cv::Mat img = cv::imread(filename, cv::IMREAD_COLOR);
    
    if (img.empty())
    {
        std::cout << "Can't load image [" << filename << "]." << std::endl;
    }
    
    cv::imwrite("saveImage.png", img);


    // Basic operations with images
    cv::Mat grayimg;
    cv::cvtColor(img, grayimg, cv::COLOR_BGR2GRAY);
    
    cv::Scalar intensity = grayimg.at<uchar>(20, 10);
    std::cout << "Intensity = " << intensity << std::endl;
    
    grayimg.at<uchar>(20,10) = 0;
    grayimg.at<uchar>(21,10) = 0;
    grayimg.at<uchar>(20,11) = 0;
    grayimg.at<uchar>(21,11) = 0;    
        
    cv::Vec3b intensity2 = img.at<cv::Vec3b>(20, 10);
    std::cout << "Intensity = " << intensity2 << std::endl;
    
    uchar blue = intensity2.val[0];
    uchar green = intensity2.val[1];
    uchar red = intensity2.val[2];
    
    std::cout << "Intensity: " << std::endl
              << "\tblue = " << (int)blue << std::endl
              << "\tgreen = " << (int)green << std::endl
              << "\tred = " << (int)red << std::endl;
    
    cv::imwrite("modifiedImage.png", grayimg);
    
    
    // Memory management and reference counting
    std::vector<cv::Point3f> points;
    
    for (int i  = 0; i < 9; ++i)
    {
        points.push_back(cv::Point3f(i, i, i));
    }
    
    cv::Mat pointsMat = cv::Mat(points).reshape(1);
    cv::Mat cloneMat = pointsMat.clone();
    
    std::cout << "pointsMat: " << pointsMat <<std::endl;
    std::cout << "cloneMat: " << cloneMat <<std::endl;
    
    points[0] = cv::Point3f(5, 5, 5);
    
    std::cout << "pointsMat: " << pointsMat <<std::endl;
    std::cout << "cloneMat: " << cloneMat <<std::endl;    
        
    
    // Primitive operations
    cv::Mat black = cv::imread("HappyFish.png", cv::IMREAD_COLOR);
    black = cv::Scalar(0);

    cv::namedWindow("Black", cv::WINDOW_AUTOSIZE);
    cv::imshow("Black", black);
    cv::waitKey();
    
    cv::Rect r(10, 10, 100, 100);
    cv::Mat smallImg = img(r);
    
    cv::namedWindow("Small", cv::WINDOW_AUTOSIZE);
    cv::imshow("Small", smallImg);
    cv::waitKey();    
    
    
    // Visualizing images
    cv::Mat valve = imread("valve.png", cv::IMREAD_COLOR);
    cv::Mat grayValve;
    cv::cvtColor(valve, grayValve, cv::COLOR_BGR2GRAY);
    
    cv::Mat sobelx;
    cv::Sobel(grayValve, sobelx, CV_32F, 1, 0);
    
    double minVal, maxVal;
    cv::minMaxLoc(sobelx, &minVal, &maxVal);
    cv::Mat draw;
    sobelx.convertTo(draw, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
    
    cv::namedWindow("Valve", cv::WINDOW_AUTOSIZE);
    cv::imshow("Valve", draw);
    cv::waitKey();
    
    
    return 0;
}
